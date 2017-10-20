package org.komparator.supplier.ws.it;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.List;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadProduct_Exception;
import org.komparator.supplier.ws.BadText_Exception;
import org.komparator.supplier.ws.ProductView;

/**
 * Test suite
 */
public class SearchProductsIT extends BaseIT {

	// static members

	// one-time initialization and clean-up
	@BeforeClass
	public static void oneTimeSetUp() throws BadProductId_Exception, BadProduct_Exception {
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
			product.setId("Y2");
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

	@AfterClass
	public static void oneTimeTearDown() {
		// clear remote service state after all tests
		client.clear();
	}

	// members

	// initialization and clean-up for each test
	@Before
	public void setUp() {
	}

	@After
	public void tearDown() {
	}

	@Test
	public void success() throws BadText_Exception, BadProductId_Exception, BadProduct_Exception  {
		List<ProductView> result = client.searchProducts("Bas");
		assertEquals(2,result.size());

//		assertEquals("Basketball",result.get(0).getDesc());		
//		assertEquals("Baseball",result.get(1).getDesc());
		assertTrue(result.get(0).getDesc().contains("Bas"));
		assertTrue(result.get(1).getDesc().contains("Bas"));
	}
	
	// bad input tests
	@Test(expected=BadText_Exception.class)
	public void nullDescriptionText() throws BadText_Exception {
		client.searchProducts(null);
	}

	@Test(expected=BadText_Exception.class)
	public void empyDescriptionText() throws BadText_Exception {
		client.searchProducts("");
	}

	@Test(expected=BadText_Exception.class)
	public void blanksDescriptionText() throws BadText_Exception {
		client.searchProducts("  ");
	}

	@Test(expected=BadText_Exception.class)
	public void newlineDescriptionText() throws BadText_Exception {
		client.searchProducts("\n");
	}

	@Test(expected=BadText_Exception.class)
	public void tabDescriptionText() throws BadText_Exception {
		client.searchProducts("\t");
	}

	@Test
	public void noMatchSearch() throws BadText_Exception{
		List<ProductView> result = client.searchProducts("Desporto");
		assertEquals(0,result.size());
	}
	
	@Test
	public void lowercaseNoMatchSearch() throws BadText_Exception {
		List<ProductView> result = client.searchProducts("basketball");
		assertEquals(0,result.size());
	}

	@Test
	public void uppercaseNoMatchSearch() throws BadText_Exception {
		List<ProductView> result = client.searchProducts("basketBall");
		assertEquals(0,result.size());
	}

	@Test
	public void exactMatchSearch() throws BadText_Exception {
		List<ProductView> result = client.searchProducts("Basketball");
		assertEquals(1,result.size());

		assertEquals("X1",result.get(0).getId());
		assertEquals(10,result.get(0).getPrice());
		assertEquals(10,result.get(0).getQuantity());
		assertEquals("Basketball",result.get(0).getDesc());
	}

	@Test
	public void exactMatchWithMiddleSpaceSearch() throws BadText_Exception {
		List<ProductView> result = client.searchProducts("Soccer ball");
		assertEquals(1,result.size());

		assertEquals("Z3",result.get(0).getId());
		assertEquals(30,result.get(0).getPrice());
		assertEquals(30,result.get(0).getQuantity());
		assertEquals("Soccer ball",result.get(0).getDesc());
	}
	
	
	// tests
	// assertEquals(expected, actual);

	// public List<ProductView> searchProducts(String descText) throws
	// BadText_Exception

	// bad input tests


	
	// main tests


}
