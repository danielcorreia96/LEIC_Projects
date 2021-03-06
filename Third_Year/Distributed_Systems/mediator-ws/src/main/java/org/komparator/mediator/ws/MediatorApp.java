package org.komparator.mediator.ws;

import java.util.Timer;

public class MediatorApp {

	private static final int LIFEPROOF_TIMER = 5000;

	public static void main(String[] args) throws Exception {
		// Check arguments
		if (args.length == 0 || args.length == 2) {
			System.err.println("Argument(s) missing!");
			System.err.println("Usage: java " + MediatorApp.class.getName() + " wsURL OR uddiURL wsName wsURL");
			return;
		}
		String uddiURL = null;
		String wsName = null;
		String wsURL = null;

		// Create server implementation object, according to options
		MediatorEndpointManager endpoint = null;
		if (args.length == 1) {
			wsURL = args[0];
			endpoint = new MediatorEndpointManager(wsURL);
		} else if (args.length >= 3) {
			uddiURL = args[0];
			wsName = args[1];
			wsURL = args[2];
			endpoint = new MediatorEndpointManager(uddiURL, wsName, wsURL);
			endpoint.setVerbose(true);
		}
		//-----------------------------
		Timer timer = new Timer(true);
		LifeProof lp = new LifeProof(endpoint);
		timer.schedule(lp, 0, LIFEPROOF_TIMER);
		//-------------------------------
		try {
			endpoint.start();
			endpoint.awaitConnections();
		} finally {
			endpoint.stop();
			lp.cancel();
			timer.cancel();
		}

	}
	
	
	


}
