package org.komparator.security.handler;

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

public class RandomNumberHandler implements SOAPHandler<SOAPMessageContext> {
	SOAPMessage soapMessage;
	SOAPPart soapPart;
	SOAPEnvelope soapEnvelope;
	SOAPHeader soapHeader;
	public static final String NAMESPACE = "http://ws.supplier.komparator.org/";
	public static final String REQUEST_PROPERTY = "my.request.property";

	
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

	private boolean processMessage(SOAPMessageContext context) {
		Boolean outbound = (Boolean) context.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
		loadSOAPComponents(context);
		if (outbound){
			System.out.println("Adding random number header to outbound SOAP message...");

			// get token from request context
			String randomNumber = (String) context.get(REQUEST_PROPERTY);
			addClientRequestIdToHeader(randomNumber);			
		}
		return true;
	}

	private void addClientRequestIdToHeader(String requestId) {
		try {
			if (soapHeader == null)
				soapHeader = soapEnvelope.addHeader();
			Name name = soapEnvelope.createName("clientRequestId","w", NAMESPACE);
			SOAPHeaderElement element = soapHeader.addHeaderElement(name);
			element.addTextNode(requestId);
		} catch (SOAPException e) {
			throw new RuntimeException("Failed to add timestamp in the SOAP message");
		}
	}

	@Override
	public boolean handleFault(SOAPMessageContext context) {
		return processMessage(context);
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
