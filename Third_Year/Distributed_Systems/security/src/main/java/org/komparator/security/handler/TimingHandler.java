package org.komparator.security.handler;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;
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

import org.w3c.dom.NodeList;

public class TimingHandler implements SOAPHandler<SOAPMessageContext> {
	SOAPMessage soapMessage;
	SOAPPart soapPart;
	SOAPEnvelope soapEnvelope;
	SOAPHeader soapHeader;
	public static final String NAMESPACE = "http://ws.supplier.komparator.org/";
	final DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss:SSS");
	
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
			System.out.println("Adding timestamp header to outbound SOAP message...");
			addTimestampToHeader();
		}
		else {
			System.out.println("Reading timestamp header of inbound SOAP message...");		
			if (soapHeader == null) {
				System.out.println("Header not found.");
				return true;
			}
			processInboundHeader();
		}
		return true;
	}

	private void processInboundHeader() {
		NodeList arguments = soapHeader.getChildNodes();
		for (int i = 0; i < arguments.getLength(); i++){
			if (arguments.item(i).getNodeName().equals("w:timeStamp")){
				String date = arguments.item(i).getTextContent();	
				checkTimestamp(date);
			}
		}
	}

	private void checkTimestamp(String date) {
		LocalDateTime now = LocalDateTime.now();
		LocalDateTime dt = LocalDateTime.parse(date, dtf);
		if (dt.until(now, ChronoUnit.SECONDS) > 3){
			throw new RuntimeException("Message sent too long ago.");
		}
		else if(dt.until(now, ChronoUnit.SECONDS) < 0){
			throw new RuntimeException("Message sent from the future.");
		}
	}

	private void addTimestampToHeader() {
		try {
			if (soapHeader == null)
				soapHeader = soapEnvelope.addHeader();
			Name name = soapEnvelope.createName("timeStamp","w", NAMESPACE);
			SOAPHeaderElement element = soapHeader.addHeaderElement(name);
			String time = LocalDateTime.now().format(dtf).toString();
			element.addTextNode(time);
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
