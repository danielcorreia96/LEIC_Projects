package org.komparator.supplier.ws.cli;


/** Main class that starts the Supplier Web Service client. */
public class SupplierClientApp {

	public static void main(String[] args) throws Exception {
		// Check arguments
		if (args.length < 2) {
			System.err.println("Argument(s) missing!");
			System.err.println("Usage: java " + SupplierClientApp.class.getName() + " <UDDIURL>" + " <ServiceName>");
			return;
		}
		String uddiURL = args[0];
		String serviceName = args[1];

		System.out.println(uddiURL);		
		System.out.println(serviceName);
		
		// Create client	
		System.out.printf("Creating client for service at %s - %s %n", uddiURL,serviceName);
		SupplierClient client = new SupplierClient(uddiURL,serviceName);

		// the following remote invocations are just basic examples
		// the actual tests are made using JUnit

		System.out.println("Invoke ping()...");
		String result = client.ping("client");
		System.out.print("Result: ");
		System.out.println(result);
	}

}
