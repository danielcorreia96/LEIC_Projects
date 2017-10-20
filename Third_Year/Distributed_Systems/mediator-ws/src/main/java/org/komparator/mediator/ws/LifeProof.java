package org.komparator.mediator.ws;

import java.util.Date;
import java.util.TimerTask;

import org.komparator.mediator.ws.cli.MediatorClient;
import org.komparator.mediator.ws.cli.MediatorClientException;

public class LifeProof extends TimerTask {
	
	private MediatorEndpointManager endpoint;
	String url = "http://localhost:8072/mediator-ws/endpoint";
	public static MediatorClient client;
	public static Date lastLifeProof;
	
	public LifeProof(MediatorEndpointManager end) {
		endpoint = end;
		try {
			client = new MediatorClient(this.url);
		} catch (MediatorClientException e) {
			System.out.println("Failed to create mediator client at LifeProof class");
		}
	}
	
	@Override
	public void run() {
		if(endpoint.isReplacedByBackup())
			return;
		
		if(!endpoint.isPrimary()){
			Date now = new Date();
			if (LifeProof.lastLifeProof != null && now.getTime() - LifeProof.lastLifeProof.getTime() > 7000){
				try {
					endpoint.publishToUDDI();
					endpoint.replaceWithBackup();
					return;
					//we don't change the "primary" flag because there is no backup server afterwards
				} catch (Exception e) {
					System.out.println("Failed to publish to UDDI...");
				}
			}
			return;
		}
		client.imAlive();
	}

}
