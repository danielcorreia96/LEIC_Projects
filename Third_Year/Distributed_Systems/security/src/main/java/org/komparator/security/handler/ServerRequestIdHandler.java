package org.komparator.security.handler;

import java.util.Set;

import javax.xml.namespace.QName;
import javax.xml.soap.SOAPEnvelope;
import javax.xml.soap.SOAPException;
import javax.xml.soap.SOAPHeader;
import javax.xml.soap.SOAPMessage;
import javax.xml.soap.SOAPPart;
import javax.xml.ws.handler.MessageContext;
import javax.xml.ws.handler.MessageContext.Scope;
import javax.xml.ws.handler.soap.SOAPHandler;
import javax.xml.ws.handler.soap.SOAPMessageContext;

import org.w3c.dom.NodeList;

public class ServerRequestIdHandler implements SOAPHandler<SOAPMessageContext> {
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
		if (!outbound){
			System.out.println("Reading random number header of inbound SOAP message...");		
			if (soapHeader == null) {
				System.out.println("Header not found.");
				return true;
			}
			processInboundHeader(context);
		}
		return true;
	}

	private void processInboundHeader(SOAPMessageContext context) {
		NodeList arguments = soapHeader.getChildNodes();
		for (int i = 0; i < arguments.getLength(); i++){
			if (arguments.item(i).getNodeName().equals("w:clientRequestId")){
				String randomNumber = arguments.item(i).getTextContent();	
				System.out.println("numero aleatorio recebido:  " + randomNumber);
				
				// put token in request context
				System.out.printf("put token '%s' on request context%n", randomNumber);
				context.put(REQUEST_PROPERTY, randomNumber);
				
				// set property scope to application so that server class can access property
				context.setScope(REQUEST_PROPERTY, Scope.APPLICATION);
			}
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
