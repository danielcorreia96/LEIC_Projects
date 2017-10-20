package org.komparator.security;

import java.io.IOException;
import java.io.InputStream;
import java.security.InvalidKeyException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.Signature;
import java.security.SignatureException;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;

public class CryptoUtil {
	/** Asymmetric cipher: combination of algorithm, block processing, and padding. **/
	private static final String ASYM_CIPHER = "RSA/ECB/PKCS1Padding";
	
	private static final String SIGNATURE_ALGO = "SHA256withRSA";
	
	/** print some error messages to standard error. */
	public static boolean outputFlag = true;
	
	public static byte[] asymCypher(byte[] plainBytes, PublicKey publicKey){
		try {
			System.out.println("Ciphering  with public key...");
			Cipher cipher = Cipher.getInstance(ASYM_CIPHER);
			cipher.init(Cipher.ENCRYPT_MODE, publicKey);
			byte[] cipherBytes = cipher.doFinal(plainBytes);		
			return cipherBytes;
		} catch (NoSuchAlgorithmException | NoSuchPaddingException e) {
			System.out.println("Failed to create cipher: missing algorithm or padding in the environment\n");
		} catch (InvalidKeyException e) {
			System.out.println("Failed to initialize cipher: invalid private key\n");
		} catch (IllegalBlockSizeException | BadPaddingException e) {
			System.out.println("Failed to cipher input\n");
		}
		throw new RuntimeException("Failed to cypher bytes");		
	}

	public static byte[] asymDecypher(byte[] cipheredBytes, PrivateKey privateKey){
		try {
			System.out.println("Deciphering  with private key...");
			Cipher cipher = Cipher.getInstance(ASYM_CIPHER);
			cipher.init(Cipher.DECRYPT_MODE, privateKey);
			byte[] decipheredBytes = cipher.doFinal(cipheredBytes);
			return decipheredBytes;
		} catch (NoSuchAlgorithmException | NoSuchPaddingException e) {
			System.out.println("Failed to create cipher: missing algorithm or padding in the environment\n");
		} catch (InvalidKeyException e) {
			System.out.println("Failed to initialize cipher: invalid private key\n");
		} catch (IllegalBlockSizeException | BadPaddingException e) {
			System.out.println("Failed to decipher input\n");
		}
		throw new RuntimeException("Failed to decypher bytes");	
	}
	

	public static byte[] makeDigitalSignature(byte[] bytes, PrivateKey privateKey) {
		try {
			System.out.println("Making Signature");
			Signature sig = Signature.getInstance(SIGNATURE_ALGO);
			sig.initSign(privateKey);
			sig.update(bytes);
			byte[] signature = sig.sign();
			return signature;	
		} catch (InvalidKeyException e) {
			System.out.println("Failed to sign: invalid private key.\n");
		} catch (NoSuchAlgorithmException e) {
			System.out.println("Failed to sign: Signature algorithm +\""+SIGNATURE_ALGO+"\" is not valid.\n");
		} catch (SignatureException e) {
			System.out.println("Caught exception while signing " + e + "\n");
		}
		throw new RuntimeException("Failed to make digital signature");
	}
	
	
	public static boolean verifyDigitalSignature(byte[] cipherDigest, byte[] bytes, PublicKey publicKey){
		try {
			System.out.println("Verifying Signature");
			Signature sig = Signature.getInstance(SIGNATURE_ALGO);
			sig.initVerify(publicKey);
			sig.update(bytes);
			return sig.verify(cipherDigest);
		} catch (SignatureException se) {
			System.err.println("Caught exception while verifying " + se + "\n");
			return false;
		} catch (InvalidKeyException e) {
			System.out.println("Failed to sign: invalid public key.\n");
			return false;
		} catch (NoSuchAlgorithmException e) {
			System.out.println("Failed to sign: Signature algorithm +\""+SIGNATURE_ALGO+"\" is not valid.\n");
			return false;
		}
	}
	
	
	/*
	 *Autenticate Certificate 
	 */
	
	public static PublicKey getPublicKeyFromCertificate(Certificate certificate) {
		return certificate.getPublicKey();
	}
	

	public static PublicKey getPublicKeyFromCertificate(String certificateResourcePath) throws CertificateException {
		InputStream certificateInputStream = getResourceAsStream(certificateResourcePath);
		
		try {
			CertificateFactory certFactory = CertificateFactory.getInstance("X.509");
			Certificate cert = certFactory.generateCertificate(certificateInputStream);
			return cert.getPublicKey();
		} finally {
			closeStream(certificateInputStream);
		}
		
	}
	public static PrivateKey getPrivateKeyFromKeyStore(String keyStoreResourcePath, char[] keyStorePassword, String keyAlias, char[] keyPassword) throws KeyStoreException{
		InputStream keyStoreInputStream = getResourceAsStream(keyStoreResourcePath);
		KeyStore keystore = KeyStore.getInstance(KeyStore.getDefaultType());
		try {
			keystore.load(keyStoreInputStream, keyStorePassword);
		} catch (NoSuchAlgorithmException | CertificateException | IOException e) {
			throw new KeyStoreException("Could not load key store", e);
		} finally {
			closeStream(keyStoreInputStream);
		}
		
		PrivateKey key = null;
		try {
			key = (PrivateKey) keystore.getKey(keyAlias, keyPassword);
		} catch (NoSuchAlgorithmException | UnrecoverableKeyException e) {
			throw new KeyStoreException(e);
		}
		return key;
	}
	
	// resource stream helpers ------------------------------------------------

	/** Method used to access resource. */
	private static InputStream getResourceAsStream(String resourcePath) {
		// uses current thread's class loader to also work correctly inside
		// application servers
		// reference: http://stackoverflow.com/a/676273/129497
		InputStream is = Thread.currentThread().getContextClassLoader().getResourceAsStream(resourcePath);
		return is;
	}
	/** Do the best effort to close the stream, but ignore exceptions. */
	private static void closeStream(InputStream in) {
		try {
			if (in != null)
				in.close();
		} catch (IOException e) {
			// ignore
		}
	}

}
