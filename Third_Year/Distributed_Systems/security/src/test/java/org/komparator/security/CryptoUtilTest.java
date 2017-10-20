package org.komparator.security;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.cert.CertificateException;

import org.junit.BeforeClass;
import org.junit.Test;

public class CryptoUtilTest {
	/** Plain text to digest. */
	private final String plainText = "Harambe did nothing wrong!";
	/** Plain text bytes. */
	private final byte[] plainBytes = plainText.getBytes();

	/** Asymmetric cryptography algorithm. */
	private static final String ASYM_ALGO = "RSA";
	/** Asymmetric cryptography key size. */
	private static final int ASYM_KEY_SIZE = 2048;
	
	private static final String CERTIFICATE = "example.cer";

	private static final String KEYSTORE = "example.jks";
	private static final String KEYSTORE_PASSWORD = "1nsecure";

	private static final String KEY_ALIAS = "example";
	private static final String KEY_PASSWORD = "ins3cur3";
	
	private static PublicKey certificatePublicKey;
	private static PrivateKey keystorePrivateKey;
	
	
	
    // static members

    // one-time initialization and clean-up
    @BeforeClass
    public static void oneTimeSetUp() throws NoSuchAlgorithmException, CertificateException, KeyStoreException {
    	// generate an RSA key pair
    	
    	certificatePublicKey = CryptoUtil.getPublicKeyFromCertificate(CERTIFICATE);
    	keystorePrivateKey = CryptoUtil.getPrivateKeyFromKeyStore(KEYSTORE, KEYSTORE_PASSWORD.toCharArray(), KEY_ALIAS, KEY_PASSWORD.toCharArray());
    }

    // Basic success Cypher-Decypher test
    @Test
    public void successCypherDecypher() {
    	byte[] cipheredBytes = CryptoUtil.asymCypher(plainBytes, certificatePublicKey);
    	byte[] decipheredBytes = CryptoUtil.asymDecypher(cipheredBytes, keystorePrivateKey);
    	String newPlainText = new String(decipheredBytes);
    	
    	assertEquals(plainText, newPlainText);
    }
    
    
    // Wrong public or private key tests
    @Test(expected = RuntimeException.class)
    public void wrongPublicKeyCipher() throws NoSuchAlgorithmException {
    	KeyPairGenerator keyGen = KeyPairGenerator.getInstance(ASYM_ALGO);
    	keyGen.initialize(ASYM_KEY_SIZE);
    	
    	byte[] cipheredBytes = CryptoUtil.asymCypher(plainBytes, keyGen.generateKeyPair().getPublic());
    	CryptoUtil.asymDecypher(cipheredBytes, keystorePrivateKey);  	

    }
    
    @Test(expected = RuntimeException.class)
    public void wrongPrivateKeyDecipher() throws NoSuchAlgorithmException {
    	KeyPairGenerator keyGen = KeyPairGenerator.getInstance(ASYM_ALGO);
    	keyGen.initialize(ASYM_KEY_SIZE);
    	
    	byte[] cipheredBytes = CryptoUtil.asymCypher(plainBytes, certificatePublicKey);
    	CryptoUtil.asymDecypher(cipheredBytes, keyGen.generateKeyPair().getPrivate());  	
    }
    
    // Tampered data tests
    @Test(expected = RuntimeException.class)
    public void tamperedCipheredBytes() {
    	byte[] cipheredBytes = CryptoUtil.asymCypher(plainBytes, certificatePublicKey);
    	
    	// data modification
    	cipheredBytes[3] = 20;
		
    	CryptoUtil.asymDecypher(cipheredBytes, keystorePrivateKey);  
    }
    
    // Wrong algorithm tests
    @Test(expected = RuntimeException.class)
    public void wrongCipherAlgorithm() throws NoSuchAlgorithmException {
    	KeyPairGenerator wrongkeyGen = KeyPairGenerator.getInstance("DSA");
    	wrongkeyGen.initialize(ASYM_KEY_SIZE);
    	KeyPair wrongkeyPair = wrongkeyGen.generateKeyPair();
    	
    	CryptoUtil.asymCypher(plainBytes, wrongkeyPair.getPublic());
    }
    
    @Test(expected = RuntimeException.class)
    public void wrongDecipherAlgorithm() throws NoSuchAlgorithmException {
    	KeyPairGenerator wrongkeyGen = KeyPairGenerator.getInstance("DSA");
    	wrongkeyGen.initialize(ASYM_KEY_SIZE);
    	KeyPair wrongkeyPair = wrongkeyGen.generateKeyPair();
    	
    	byte[] cipheredBytes = CryptoUtil.asymCypher(plainBytes, certificatePublicKey);
    	CryptoUtil.asymDecypher(cipheredBytes, wrongkeyPair.getPrivate());  	
    } 
    
  //basic success Signature test
    @Test
    public void successSignature() {
    	byte[] cipherDigest = CryptoUtil.makeDigitalSignature(plainBytes, keystorePrivateKey);
    	boolean result = CryptoUtil.verifyDigitalSignature(cipherDigest, plainBytes, certificatePublicKey);
    	assertTrue(result);
    }
    
    @Test
    public void tamperedSignature() {
    	byte[] signatureDigest = CryptoUtil.makeDigitalSignature(plainBytes, keystorePrivateKey);
    	signatureDigest[3] = 20;
    	boolean result = CryptoUtil.verifyDigitalSignature(signatureDigest, plainBytes, certificatePublicKey);
    	assertFalse(result);
    }
    
    

}
