package org.komparator.security;

import java.security.PublicKey;
import java.security.cert.Certificate;
import java.util.HashMap;
import java.util.Map;

public class KomparatorSecurityManager {
	
	public String name = "unknown";
	public static Map<String,PublicKey> pubKeysMap = new HashMap<>();
	
	private KomparatorSecurityManager(){	
	}
	
	private static class SingletonHolder {
		private static final KomparatorSecurityManager INSTANCE = new KomparatorSecurityManager();
	
	}

		public static synchronized KomparatorSecurityManager getInstance() {
			return SingletonHolder.INSTANCE;
		
		}	
		public static String getName(){
			return getInstance().name;
		}
		public static void setName(String name){
			getInstance().name=name;
		}
		public static void savePubKeyInMapWithCert(String name,Certificate certificate){
			pubKeysMap.put(name,certificate.getPublicKey());
		}
		public static void savePubKeyInMap(String name,PublicKey key){
			pubKeysMap.put(name,key);
		}
		public static boolean hasCertificateInMap(String name){
			return pubKeysMap.containsKey(name);
		}
		
		public static PublicKey getCertKeyFromMap(String name){
			return pubKeysMap.get(name);
		}	
		
}
