package org.komparator.supplier.ws;


/** Main class that starts the Supplier Web Service. */
public class SupplierApp {

	public static void main(String[] args) throws Exception {
		// Check arguments
		if (args.length < 3) {
			System.err.println("Argument(s) missing!");
			System.err.println("Usage: java " + SupplierApp.class.getName() + " <UDDIURL>" + " <ServiceName>" + " <WSURL>");
			return;
		}
		String uddiURL = args[0];
		String serviceName = args[1];
		String wsURL = args[2];

		// Create server implementation object
		SupplierEndpointManager endpoint = new SupplierEndpointManager(uddiURL, serviceName, wsURL);
		try {
			endpoint.start();
			
			endpoint.awaitConnections();
		} finally {
			endpoint.stop();
		}

	}

}
