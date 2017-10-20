package org.komparator.supplier.ws;

import java.io.IOException;

import javax.xml.ws.Endpoint;

import org.komparator.security.KomparatorSecurityManager;

import pt.ulisboa.tecnico.sdis.ws.uddi.UDDINaming;
import pt.ulisboa.tecnico.sdis.ws.uddi.UDDINamingException;


/** End point manager */
public class SupplierEndpointManager {

	/** Web Service location to publish */
	private String wsURL = null;
	private String uddiURL = null;
	private String serviceName = null;

	/** Port implementation */
	private SupplierPortImpl portImpl = new SupplierPortImpl(this);

	/** Obtain Port implementation */
	public SupplierPortType getPort() {
		return portImpl;
	}

	/** Web Service end point */
	private Endpoint endpoint = null;

	/** output option **/
	private boolean verbose = true;

	public boolean isVerbose() {
		return verbose;
	}

	public void setVerbose(boolean verbose) {
		this.verbose = verbose;
	}

	/** constructor with provided web service URL */
	public SupplierEndpointManager(String wsURL) {
		if (wsURL == null)
			throw new NullPointerException("Web Service URL cannot be null!");
		this.wsURL = wsURL;
	}
	
	public SupplierEndpointManager(String uddiURL, String serviceName, String wsURL) {
		if (uddiURL == null)
			throw new NullPointerException("uddi URL cannot be null!");
		if (serviceName == null)
			throw new NullPointerException("Service Name cannot be null!");
		if (wsURL == null)
			throw new NullPointerException("Web Service URL cannot be null!");
		this.uddiURL = uddiURL;
		this.serviceName=serviceName;
		this.wsURL = wsURL;
		this.registerUDDI();
		KomparatorSecurityManager.setName(serviceName);
		System.out.println("Singleton Name is..." + KomparatorSecurityManager.getName() + "!!!");	
	}
	private void registerUDDI() {
		System.out.printf("Publishing '%s' to UDDI at %s%n", this.serviceName, uddiURL);
		UDDINaming uddiNaming;
		try {
			uddiNaming = new UDDINaming(uddiURL);
			uddiNaming.rebind(this.serviceName, this.wsURL);

		} catch (UDDINamingException e) {
			System.out.println("Error: couldn't execute rebind method on UDDI");
		}
		finally{
			if (endpoint != null){
				endpoint.stop();
				System.out.printf("Stopped %s%n", this.uddiURL);
			}
		}
		
	}

	/* end point management */

	public void start() throws Exception {
		try {
			// publish end point
			endpoint = Endpoint.create(this.portImpl);
			if (verbose) {
				System.out.printf("Starting %s%n", wsURL);
			}
			endpoint.publish(wsURL);
		} catch (Exception e) {
			endpoint = null;
			if (verbose) {
				System.out.printf("Caught exception when starting: %s%n", e);
			}
			throw e;
		}
	}

	public void awaitConnections() {
		if (verbose) {
			System.out.println("Awaiting connections");
			System.out.println("Press enter to shutdown");
		}
		try {
			System.in.read();
		} catch (IOException e) {
			if (verbose) {
				System.out.printf("Caught i/o exception when awaiting requests: %s%n", e);
			}
		}
	}

	public void stop() throws Exception {
		try {
			if (endpoint != null) {
				// stop end point
				endpoint.stop();
				if (verbose) {
					System.out.printf("Stopped %s%n", wsURL);
				}
			}
		} catch (Exception e) {
			if (verbose) {
				System.out.printf("Caught exception when stopping: %s%n", e);
			}
		}
		this.portImpl = null;
	}

}
