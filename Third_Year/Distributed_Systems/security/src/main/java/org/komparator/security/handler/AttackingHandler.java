package org.komparator.security.handler;

import java.util.Set;

import javax.xml.namespace.QName;
import javax.xml.soap.SOAPBody;
import javax.xml.soap.SOAPEnvelope;
import javax.xml.soap.SOAPHeader;
import javax.xml.soap.SOAPMessage;
import javax.xml.soap.SOAPPart;
import javax.xml.ws.handler.MessageContext;
import javax.xml.ws.handler.soap.SOAPHandler;
import javax.xml.ws.handler.soap.SOAPMessageContext;

import org.w3c.dom.NodeList;

public class AttackingHandler implements SOAPHandler<SOAPMessageContext> {
	public static final String NAMESPACE = "http://ws.supplier.komparator.org/";

	@Override
	public boolean handleMessage(SOAPMessageContext context) {
		Boolean outbound = (Boolean) context.get(MessageContext.MESSAGE_OUTBOUND_PROPERTY);
		try{
			if (outbound){
				System.out.println("Attacking outbound SOAP message...");
				SOAPMessage soapMessage = context.getMessage();
				SOAPPart soapPart = soapMessage.getSOAPPart();
				SOAPEnvelope soapEnvelope = soapPart.getEnvelope();
				SOAPBody soapBody = soapMessage.getSOAPBody();
				SOAPHeader soapHeader = soapEnvelope.getHeader();
				if (soapHeader == null)
					soapHeader = soapEnvelope.addHeader();
				
				System.out.println("Initializing getProdResponse variable with -> " + context.get(MessageContext.WSDL_OPERATION));
				QName getProdResponse = (QName) context.get(MessageContext.WSDL_OPERATION);
				if (!getProdResponse.getLocalPart().equals("getProduct")) {
					System.out.println("Not a getProduct message!! :<");
					return true;
				}
				System.out.println("Found a getProduct message!!");
				
				NodeList arguments = soapBody.getFirstChild().getFirstChild().getChildNodes();
				String plainTextProductId = null;
				for (int i = 0; i<arguments.getLength();i++){
					if (arguments.item(i).getNodeName().equals("id")){
						plainTextProductId = arguments.item(i).getTextContent();
						System.out.println("Found productId -> " + plainTextProductId);
					}
				}
				if (plainTextProductId.equals("HARAMBE")) {
					System.out.println("\nIt's HARAMBE time!\n");
					
					for (int i = 0; i<arguments.getLength();i++){
						if (arguments.item(i).getNodeName().equals("price")){
							String currentPrice = arguments.item(i).getTextContent();
							System.out.println("Current price:" + currentPrice);
							
							int newPriceValue = Integer.parseInt(currentPrice) + 656;
							System.out.println("New price value:" + newPriceValue);
							
							String plainTextNewPrice = String.valueOf(newPriceValue);
							System.out.println("New price string:" + plainTextNewPrice);
							
							arguments.item(i).setTextContent(plainTextNewPrice);
							soapMessage.saveChanges();
							return true;
						}	
					}
				}
				else{
					System.out.println("It's not HARAMBE... (keep waiting)");
					return true;
				}
			}
			else{
				System.out.println("Attacking inbound SOAP message...");
				
				SOAPMessage soapMessage = context.getMessage();
				SOAPPart soapPart = soapMessage.getSOAPPart();
				SOAPEnvelope soapEnvelope = soapPart.getEnvelope();
				SOAPHeader soapHeader = soapEnvelope.getHeader();
				
				if (soapHeader == null) {
					System.out.println("Header not found.");
					return true;
				}
				
			}
		}
		catch (Exception e) {
			System.out.print("Caught exception in handleMessage: ");
			System.out.println(e);
			System.out.println("Continue normal processing...");
		}
		return true;
	}
	
	@Override
	public void close(MessageContext arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean handleFault(SOAPMessageContext context) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public Set<QName> getHeaders() {
		// TODO Auto-generated method stub
		return null;
	}

}
