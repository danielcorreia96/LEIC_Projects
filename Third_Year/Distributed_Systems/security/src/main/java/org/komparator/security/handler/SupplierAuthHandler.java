package org.komparator.security.handler;


import static javax.xml.bind.DatatypeConverter.parseBase64Binary;
import static javax.xml.bind.DatatypeConverter.printBase64Binary;


import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.security.KeyStoreException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.util.Set;

import javax.xml.namespace.QName;
import javax.xml.soap.Name;
import javax.xml.soap.SOAPEnvelope;
import javax.xml.soap.SOAPException;
import javax.xml.soap.SOAPHeader;
import javax.xml.soap.SOAPHeaderElement;
import javax.xml.soap.SOAPMessage;
import javax.xml.soap.SOAPPart;
import javax.xml.ws.handler.MessageContext;
import javax.xml.ws.handler.soap.SOAPHandler;
import javax.xml.ws.handler.soap.SOAPMessageContext;

import org.komparator.security.CertUtil;
import org.komparator.security.CryptoUtil;
import org.komparator.security.KomparatorSecurityManager;
import org.w3c.dom.NodeList;

import pt.ulisboa.tecnico.sdis.ws.cli.CAClient;
import pt.ulisboa.tecnico.sdis.ws.cli.CAClientException;

public class SupplierAuthHandler implements SOAPHandler<SOAPMessageContext> {
	private static final char[] KEYSTORE_PASSWORD = "t3gkkV2w".toCharArray();
	public static final String NAMESPACE = "http://ws.supplier.komparator.org/";
	private static final String CA_WSURL = "http://sec.sd.rnl.tecnico.ulisboa.pt:8081/ca";
	SOAPMessage soapMessage; 
	SOAPPart soapPart;
	SOAPEnvelope soapEnvelope ;
	SOAPHeader soapHeader;

	private void loadSOAPComponents(SOAPMessageContext context){
		try {
			soapMessage = context.getMessage();
			soapPart = soapMessage.getSOAPPart();
			soapEnvelope = soapPart.getEnvelope();
			soapHeader = soapEnvelope.getHeader();
		} catch (SOAPException e) {
			throw new RuntimeException("Failed to load a component of the SOAP message");
		}
	}
	
	@Override
	public boolean handleMessage(SOAPMessageContext context) {
		return processMessage(context);
	}

	private boolean processMessage(SOAPMessageContext context) throws RuntimeException {
		Boolean outbound = (Boolean) context.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
		loadSOAPComponents(context);
		if (outbound) {
			System.out.println("SupplierAuth handler outgoing stuff...");			
			String serviceName = KomparatorSecurityManager.getName();
			addServiceNameToHeader(serviceName);

			byte[] signature = signMessage(serviceName, soapMessage);
			addSignatureToHeader(soapEnvelope, soapHeader, signature);
			return true;		
		}
		else {
			System.out.println("Reading header at supplierAuth handler of inbound SOAP message...");				
			if (soapHeader == null) {
				throw new RuntimeException("Expected header with signature...");
			}
			NodeList arguments = soapHeader.getChildNodes();
			String plainTextServiceName = getServiceNameFromHeader(arguments);
			String plainTextSignature = getSignatureFromHeader(arguments);
			PublicKey pubKey = getPublicKeyToVerifySign(plainTextServiceName, plainTextSignature);
			boolean messageIsVerified = verifySignature(soapMessage, plainTextSignature, pubKey);
			if (!messageIsVerified) {
				throw new RuntimeException("Signature verification failed!");
			}
			return true;
		}
	}

	private void addServiceNameToHeader(String serviceName){
		try {
			if (soapHeader == null) {
				soapHeader= soapEnvelope.addHeader();
			}
			Name serviceHeaderName = soapEnvelope.createName("serviceName","w", NAMESPACE);
			SOAPHeaderElement serviceHeaderElement = soapHeader.addHeaderElement(serviceHeaderName);
			serviceHeaderElement.addTextNode(serviceName);
		} catch (SOAPException e) {
			throw new RuntimeException("Failed Manipulation on SoapObjects");
		}
	}

	private PublicKey getPublicKeyToVerifySign(String plainTextServiceName, String plainTextSignature){
		if(KomparatorSecurityManager.hasCertificateInMap(plainTextServiceName)){
			System.out.println("Already had  " + plainTextServiceName + " service key locally");
			return KomparatorSecurityManager.getCertKeyFromMap(plainTextServiceName);
		}
		else {
			try{
				System.out.println("Don't have " + plainTextServiceName+ "service key locally: Getting Key From Authority");
				PublicKey pubKey = getPubKeyFromCA(plainTextServiceName);
				KomparatorSecurityManager.savePubKeyInMap(plainTextServiceName, pubKey);
				System.out.println("Saved " + plainTextServiceName + " service key locally");
				return pubKey;
			} catch (CAClientException e) {
				throw new RuntimeException("Failed to Create client that connects to Authority");
			} catch (CertificateException e) {
				throw new RuntimeException("Failed to get Public Key from Certificate");
			}
		}
	}

	private String getSignatureFromHeader(NodeList arguments){
		for (int i = 0; i<arguments.getLength();i++){
			if (arguments.item(i).getNodeName().equals("w:signature")){
				String signature = arguments.item(i).getTextContent();
				soapHeader.removeChild(arguments.item(i));
				return signature;
			}
		}
		throw new RuntimeException("Couldn't find the signature in header");
	}

	private String getServiceNameFromHeader(NodeList arguments) {
		for (int i = 0; i<arguments.getLength();i++){
			if (arguments.item(i).getNodeName().equals("w:serviceName")){
				return arguments.item(i).getTextContent();
			}
		}
		throw new RuntimeException("Couldn't find the service name in header");
	}

	private void addSignatureToHeader(SOAPEnvelope soapEnvelope, SOAPHeader soapHeader, byte[] signature){
		try {
			Name name = soapEnvelope.createName("signature","w", NAMESPACE);
			SOAPHeaderElement element = soapHeader.addHeaderElement(name);
			String encodedSignature = printBase64Binary(signature);
			element.addTextNode(new String(encodedSignature));
		} catch (SOAPException e) {
			throw new RuntimeException("Failed to manipulate added header");
		}
	}

	private boolean verifySignature(SOAPMessage soapMessage, String plainTextSignature, PublicKey pubKey){
		try{
			byte[] secretBytes = parseBase64Binary(plainTextSignature);
			ByteArrayOutputStream byteStream= new ByteArrayOutputStream();
			soapMessage.writeTo(byteStream);
			byte[] messageBytes = byteStream.toByteArray();
			boolean messageIsVerified = CryptoUtil.verifyDigitalSignature(secretBytes, messageBytes, pubKey);
			return messageIsVerified;
		} catch (IOException e) {
			throw new RuntimeException("Failed to Write Message on byteSteam for Signature verification");
		} catch (SOAPException e) {
			throw new RuntimeException("Failed to write SoapMessage");
		}
	}
	
	private byte[] signMessage(String serviceName, SOAPMessage soapMessage) {
		try {
			ByteArrayOutputStream byteStream= new ByteArrayOutputStream();
			soapMessage.writeTo(byteStream);
			byte[] messageBytes = byteStream.toByteArray();

			String keystoreFilename = "src/main/resources/" + serviceName + ".jks";
			PrivateKey privKey = CertUtil.getPrivateKeyFromKeyStoreFile(keystoreFilename, KEYSTORE_PASSWORD, serviceName.toLowerCase(), KEYSTORE_PASSWORD);
			byte[] signature = CryptoUtil.makeDigitalSignature(messageBytes, privKey);
			return signature;
		} catch (SOAPException e) {
			throw new RuntimeException("Failed to write SoapMessage");
		} catch (FileNotFoundException e) {
			throw new RuntimeException("Private Key for signing is not on KeyStore");
		} catch (IOException e) {
			throw new RuntimeException("Failed to Write Message on byteSteam for Signature");
		} catch (UnrecoverableKeyException e) {
			throw new RuntimeException("Failed to get Private Key from KeyStore with and Unrecoverable Exception");
		} catch (KeyStoreException e) {
			throw new RuntimeException("Failed to get Private Key from KeyStore");
		}
	}

	private PublicKey getPubKeyFromCA(String serviceName) throws CAClientException, CertificateException {
		CAClient ca = new CAClient(CA_WSURL);
		String certifString = ca.getCertificate(serviceName);
		Certificate cert = CertUtil.getX509CertificateFromPEMString(certifString);
		PublicKey caCertificate = CryptoUtil.getPublicKeyFromCertificate("ca.cer");
		if (!CertUtil.verifySignedCertificate(cert, caCertificate)){
			throw new RuntimeException();
		}
		return cert.getPublicKey();
	}
	
	@Override
	public Set<QName> getHeaders() {
		// TODO Auto-generated method stub
		return null;
	}
	

	@Override
	public void close(MessageContext context) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean handleFault(SOAPMessageContext context) {
		return processMessage(context);
	}


}