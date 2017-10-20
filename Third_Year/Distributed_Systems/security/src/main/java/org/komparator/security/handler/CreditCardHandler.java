package org.komparator.security.handler;

import static javax.xml.bind.DatatypeConverter.parseBase64Binary;
import static javax.xml.bind.DatatypeConverter.printBase64Binary;

import java.security.KeyStoreException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.time.format.DateTimeFormatter;
import java.util.Set;

import javax.xml.namespace.QName;
import javax.xml.soap.SOAPBody;
import javax.xml.soap.SOAPEnvelope;
import javax.xml.soap.SOAPException;
import javax.xml.soap.SOAPHeader;
import javax.xml.soap.SOAPMessage;
import javax.xml.soap.SOAPPart;
import javax.xml.ws.handler.MessageContext;
import javax.xml.ws.handler.soap.SOAPHandler;
import javax.xml.ws.handler.soap.SOAPMessageContext;

import org.komparator.security.CertUtil;
import org.komparator.security.CryptoUtil;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import pt.ulisboa.tecnico.sdis.ws.cli.CAClient;
import pt.ulisboa.tecnico.sdis.ws.cli.CAClientException;

public class CreditCardHandler implements SOAPHandler<SOAPMessageContext> {
	private static final String KEYSTORE_ALIAS = "a52_mediator";
	private static final char[] KEYSTORE_PASSWORD = "t3gkkV2w".toCharArray();
	private static final String MEDIATOR_KEYSTORE = "A52_Mediator.jks";
	private static final String MEDIATOR_SERVICE_NAME = "A52_Mediator";
	private static final String CA_WSURL = "http://sec.sd.rnl.tecnico.ulisboa.pt:8081/ca";
	public static final String NAMESPACE = "http://ws.mediator.komparator.org/";
	final DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss:SSS");
	SOAPMessage soapMessage;
	SOAPPart soapPart;
	SOAPEnvelope soapEnvelope;
	SOAPBody soapBody;
	SOAPHeader soapHeader;
	
	private void loadSOAPComponents(SOAPMessageContext context){
		try {
			soapMessage = context.getMessage();
			soapPart = soapMessage.getSOAPPart();
			soapEnvelope = soapPart.getEnvelope();
			soapBody = soapMessage.getSOAPBody();
			soapHeader = soapEnvelope.getHeader();
		} catch (SOAPException e) {
			throw new RuntimeException("Failed to load a component of the SOAP message");
		}
	}
	
	@Override
	public boolean handleMessage(SOAPMessageContext context) {
		Boolean outbound = (Boolean) context.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
		QName operation = (QName) context.get(MessageContext.WSDL_OPERATION);	
		loadSOAPComponents(context);
		Node creditCardNode = getCreditCardNumberNode();
		if(creditCardNode == null || !operation.getLocalPart().equals("buyCart")){
			System.out.println("This is not a buyCart requestd message. Skip cypher/decypher processing...");
			return true;
		} 
		if (outbound) {
			System.out.println("CreditCard handler outgoing stuff...");
			cypherCreditCardNumber(creditCardNode);	
		}
		else {
			System.out.println("CreditCard handler inbound stuff...");	
			decypherCreditCardNumber(creditCardNode);
		}
		return true;
	}

	private Node getCreditCardNumberNode() {
		NodeList arguments = soapBody.getFirstChild().getChildNodes();
		for (int i = 0; i < arguments.getLength(); i++){
			if (arguments.item(i).getNodeName().equals("creditCardNr")){
				return arguments.item(i);
			}
		}
		return null;
	}
	
	private void decypherCreditCardNumber(Node creditCardNode) {
		try {
			PrivateKey privKey = CryptoUtil.getPrivateKeyFromKeyStore(MEDIATOR_KEYSTORE, KEYSTORE_PASSWORD, KEYSTORE_ALIAS, KEYSTORE_PASSWORD);
			byte[] secretBytes = parseBase64Binary(creditCardNode.getTextContent());	
			byte[] decipheredBytes = CryptoUtil.asymDecypher(secretBytes, privKey);
			creditCardNode.setTextContent(new String(decipheredBytes));
		} catch (KeyStoreException e) {
			throw new RuntimeException("Failed to decrypt the credit card number");
		}
	}

	private void cypherCreditCardNumber(Node creditCardNode) {
		try {
			byte[] plainBytes = creditCardNode.getTextContent().getBytes();
			byte[] cipheredBytes = CryptoUtil.asymCypher(plainBytes, getPubKeyFromCA());
			String encoded = printBase64Binary(cipheredBytes);
			creditCardNode.setTextContent(encoded);
		} catch (CertificateException | CAClientException e) {
			throw new RuntimeException("Failed to encrypt the credit card number");
		} 
	}

	private PublicKey getPubKeyFromCA() throws CAClientException, CertificateException {
		CAClient ca = new CAClient(CA_WSURL);
		String certifString = ca.getCertificate(MEDIATOR_SERVICE_NAME);
		Certificate cert = CertUtil.getX509CertificateFromPEMString(certifString);
		PublicKey caCertificate = CryptoUtil.getPublicKeyFromCertificate("ca.cer");
		if (!CertUtil.verifySignedCertificate(cert, caCertificate)){
			throw new RuntimeException("The public key from CA web service is invalid!");
		}
		return cert.getPublicKey();
	}

	@Override
	public boolean handleFault(SOAPMessageContext context) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void close(MessageContext context) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public Set<QName> getHeaders() {
		// TODO Auto-generated method stub
		return null;
	}

}
