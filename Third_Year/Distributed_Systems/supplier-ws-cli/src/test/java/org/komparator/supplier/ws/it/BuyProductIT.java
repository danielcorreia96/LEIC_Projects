package org.komparator.supplier.ws.it;

import static org.junit.Assert.assertEquals;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadProduct_Exception;
import org.komparator.supplier.ws.BadQuantity_Exception;
import org.komparator.supplier.ws.InsufficientQuantity_Exception;
import org.komparator.supplier.ws.ProductView;

/**
 * Test suite
 */
public class BuyProductIT extends BaseIT {

	// static members

	// one-time initialization and clean-up
	@Before
	public void setUp() throws BadProductId_Exception, BadProduct_Exception {
		// clear remote service state before all tests
		client.clear();

		// fill-in test products
		// (since getProduct is read-only the initialization below
		// can be done once for all tests in this suite)
		{
			ProductView product = new ProductView();
			product.setId("X1");
			product.setDesc("Basketball");
			product.setPrice(10);
			product.setQuantity(10);
			client.createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("y2");
			product.setDesc("Baseball");
			product.setPrice(20);
			product.setQuantity(20);
			client.createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId("Z3");
			product.setDesc("Soccer ball");
			product.setPrice(30);
			product.setQuantity(30);
			client.createProduct(product);
		}
	}


	// members

	// initialization and clean-up for each test


	@After
	public void tearDown() {
		client.clear();
	}
	
	
	@Test(expected=InsufficientQuantity_Exception.class)
	public void success( )throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception{
		String id=client.buyProduct("X1", 5); // since quantity is 10, we assume this is working
		Assert.assertNotNull(id);
		
		client.buyProduct("X1", 6); // this should throw the expected exception
	}

	// bad input tests

	@Test(expected=BadProductId_Exception.class)
	public void nullProductId() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception{
		client.buyProduct(null, 1);
	}

	@Test(expected=BadProductId_Exception.class)
	public void emptyProductId() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception{
		client.buyProduct("", 1);
	}
	
	@Test(expected=BadProductId_Exception.class)
	public void whitespaceProductId() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception{
		client.buyProduct("   ", 1);
	}
	@Test(expected = BadProductId_Exception.class)
	public void tabProductId() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("\t", 1);
	}

	@Test(expected = BadProductId_Exception.class)
	public void newlineProductId() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("\n", 1);
	}

	@Test(expected = BadProductId_Exception.class)
	public void pointProductId() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct(".X1", 1);
	}

	@Test(expected = BadProductId_Exception.class)
	public void underscoreProductId() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("_X1", 1);
	}

	@Test(expected = BadProductId_Exception.class)
	public void middlespaceProductId() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("X 1", 1);
	}

	@Test(expected = BadQuantity_Exception.class)
	public void negativeQuantity() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("X1", -1);
	}

	@Test(expected = BadQuantity_Exception.class)
	public void zeroQuantity() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("X1", 0);
	}
	
	@Test(expected = InsufficientQuantity_Exception.class)
	public void buyTooMany() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("X1", 11);
	}

	@Test(expected = InsufficientQuantity_Exception.class)
	public void buyWhenQuantityIsZero() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		client.buyProduct("X1", 10); // just to set the quantity to zero

		client.buyProduct("X1", 1);
	}

	@Test
	public void buyNotExistsProduct() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		String result = client.buyProduct("X1000", 1);
		Assert.assertNull(result);
	} 
	
	@Test
	public void buyLowercaseNotExistsProduct() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		String result = client.buyProduct("x1", 1);
		Assert.assertNull(result);
	} 

	@Test
	public void buyUppercaseNotExistsProduct() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		String result = client.buyProduct("Y2", 1);
		Assert.assertNull(result);
	} 

	@Test
	public void buyMaximumQuantity() throws BadProductId_Exception, BadQuantity_Exception, InsufficientQuantity_Exception {
		String id = client.buyProduct("X1", 10);
		Assert.assertNotNull(id);
		
		assertEquals(client.getProduct("X1").getQuantity(), 0);
	}

	// tests
	// assertEquals(expected, actual);

	// public String buyProduct(String productId, int quantity)
	// throws BadProductId_Exception, BadQuantity_Exception,
	// InsufficientQuantity_Exception {

	// bad input tests

	

	// main tests

	
}
