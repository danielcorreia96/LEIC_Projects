package org.komparator.mediator.ws.it;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.List;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.komparator.mediator.ws.InvalidText_Exception;
import org.komparator.mediator.ws.ItemView;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadProduct_Exception;
import org.komparator.supplier.ws.ProductView;

public class SearchItemsIT extends BaseIT{

	private static final String P3 = "Z3";
	private static final String P2 = "Y2";
	private static final String P1 = "X1";

	@BeforeClass
	public static void oneTimeSetUp() throws BadProductId_Exception, BadProduct_Exception {
		// clear remote service state before all tests
		mediatorClient.clear();

		// fill-in test products
		// (since getProduct is read-only the initialization below
		// can be done once for all tests in this suite)
		{
			ProductView product = new ProductView();
			product.setId(P1);
			product.setDesc("Basketball");
			product.setPrice(10);
			product.setQuantity(10);
			supplierClient1.createProduct(product);
			product.setPrice(50);
			supplierClient2.createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId(P2);
			product.setDesc("Baseball");
			product.setPrice(20);
			product.setQuantity(20);
			supplierClient1.createProduct(product);
		}
		{
			ProductView product = new ProductView();
			product.setId(P3);
			product.setDesc("Soccer ball");
			product.setPrice(30);
			product.setQuantity(30);
			supplierClient2.createProduct(product);
		}
	}

	@AfterClass
	public static void oneTimeTearDown() {
		// clear remote service state after all tests
		mediatorClient.clear ();
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
	public void success() throws InvalidText_Exception, BadProductId_Exception, BadProduct_Exception  {
		List<ItemView> result = mediatorClient.searchItems("Bas");
		assertEquals(3,result.size());

//		assertEquals("Basketball",result.get(0).getDesc());		
//		assertEquals("Baseball",result.get(1).getDesc());
		assertTrue(result.get(0).getDesc().contains("Bas"));
		assertTrue(result.get(1).getDesc().contains("Bas"));
		assertTrue(result.get(2).getDesc().contains("Bas"));

		assertEquals(supplierClient1.getServiceName(), result.get(0).getItemId().getSupplierId());
		assertEquals(P1, result.get(0).getItemId().getProductId());
		assertEquals(10, result.get(0).getPrice());
		
		assertEquals(supplierClient2.getServiceName(), result.get(1).getItemId().getSupplierId());
		assertEquals(P1, result.get(1).getItemId().getProductId());
		assertEquals(50, result.get(1).getPrice());
		
		assertEquals(supplierClient1.getServiceName(), result.get(2).getItemId().getSupplierId());
		assertEquals(P2, result.get(2).getItemId().getProductId());
		assertEquals(20, result.get(2).getPrice());
		

	}
	
	// bad input tests
	@Test(expected=InvalidText_Exception.class)
	public void nullDescriptionText() throws InvalidText_Exception {
		mediatorClient.searchItems(null);
	}

	@Test(expected=InvalidText_Exception.class)
	public void empyDescriptionText() throws InvalidText_Exception {
		mediatorClient.searchItems("");
	}

	@Test(expected=InvalidText_Exception.class)
	public void blanksDescriptionText() throws InvalidText_Exception {
		mediatorClient.searchItems("  ");
	}

	@Test(expected=InvalidText_Exception.class)
	public void newlineDescriptionText() throws InvalidText_Exception {
		mediatorClient.searchItems("\n");
	}

	@Test(expected=InvalidText_Exception.class)
	public void tabDescriptionText() throws InvalidText_Exception {
		mediatorClient.searchItems("\t");
	}

	@Test
	public void noMatchSearch() throws InvalidText_Exception{
		List<ItemView> result = mediatorClient.searchItems("Desporto");
		assertEquals(0,result.size());
	}
	
	@Test
	public void lowercaseNoMatchSearch() throws InvalidText_Exception {
		List<ItemView> result = mediatorClient.searchItems("basketball");
		assertEquals(0,result.size());
	}

	@Test
	public void uppercaseNoMatchSearch() throws InvalidText_Exception {
		List<ItemView> result = mediatorClient.searchItems("basketBall");
		assertEquals(0,result.size());
	}
	
	@Test
	public void sameDescriptionMustComeInOrder() throws InvalidText_Exception{
		List<ItemView> result = mediatorClient.searchItems("Basketball");
		assertEquals(2,result.size());

		assertTrue(result.get(0).getDesc().contains("Basketball"));
		assertTrue(result.get(1).getDesc().contains("Basketball"));

		assertEquals(supplierClient1.getServiceName(), result.get(0).getItemId().getSupplierId() );
		assertEquals( P1, result.get(0).getItemId().getProductId());
		assertEquals(10, result.get(0).getPrice());
		
		
		assertEquals(supplierClient2.getServiceName(), result.get(1).getItemId().getSupplierId() );
		assertEquals( P1, result.get(1).getItemId().getProductId());
		assertEquals(50, result.get(1).getPrice());
	}

	@Test
	public void exactMatchWithMiddleSpaceSearch() throws InvalidText_Exception {
		List<ItemView> result = mediatorClient.searchItems("Soccer ball");
		assertEquals(1,result.size());

		assertEquals(P3,result.get(0).getItemId().getProductId());
		assertEquals(30,result.get(0).getPrice());
		assertEquals("Soccer ball",result.get(0).getDesc());
	}
	
}
