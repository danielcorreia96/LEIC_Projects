package org.komparator.mediator.ws.it;

import static org.junit.Assert.assertEquals;

import java.util.List;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.komparator.mediator.ws.InvalidItemId_Exception;
import org.komparator.mediator.ws.ItemView;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadProduct_Exception;
import org.komparator.supplier.ws.ProductView;
import org.komparator.supplier.ws.cli.SupplierClient;
import org.komparator.supplier.ws.cli.SupplierClientException;


public class GetItemsIT extends BaseIT {
	// static members
	static ProductView product1 = new ProductView();
	// one-time initialization and clean-up
	@Before 
	public  void oneTimeSetUp() throws BadProductId_Exception, BadProduct_Exception {
		mediatorClient.clear();
		product1.setId("X1");
		product1.setDesc("Basketball");
		product1.setPrice(10);
		product1.setQuantity(10);

		ProductView product2 = new ProductView();
		product2.setId("Y2");
		product2.setDesc("Baseball");
		product2.setPrice(20);
		product2.setQuantity(20);

		ProductView product3 = new ProductView();
		product3.setId("z3");
		product3.setDesc("Soccer ball");
		product3.setPrice(30);
		product3.setQuantity(30);
		
		supplierClient1.createProduct(product1);
		supplierClient1.createProduct(product2);
		
		product1.setPrice(50);
		product1.setQuantity(5);
		supplierClient2.createProduct(product1);
		supplierClient2.createProduct(product3);
	}

	@After
	public  void oneTimeTearDown() {
		// clear remote service state after all tests
		mediatorClient.clear();
	}
	
	// Bad input tests
	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsNullTest() throws InvalidItemId_Exception {
		mediatorClient.getItems(null);
	}

	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsEmptyTest() throws InvalidItemId_Exception {
		mediatorClient.getItems("");
	}

	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsWhitespaceTest() throws InvalidItemId_Exception {
		mediatorClient.getItems(" ");
	}

	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsTabTest() throws InvalidItemId_Exception {
		mediatorClient.getItems("\t");
	}

	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsNewlineTest() throws InvalidItemId_Exception {
		mediatorClient.getItems("\n");
	}

	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsPointTest() throws InvalidItemId_Exception {
		mediatorClient.getItems(".X1");
	}

	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsUnderscoreTest() throws InvalidItemId_Exception {
		mediatorClient.getItems("_X1");
	}

	@Test(expected = InvalidItemId_Exception.class)
	public void getItemsMiddlespaceTest() throws InvalidItemId_Exception{
		mediatorClient.getItems("X 1");
	}
	
	// Main tests - success
	@Test
	public void getNonExistingItem() throws InvalidItemId_Exception {
		List<ItemView> resultList = mediatorClient.getItems("A1");
		assertEquals(0, resultList.size());
	}
	
	@Test
	public void getItemFromOneSupplier() throws InvalidItemId_Exception {
		List<ItemView> resultList = mediatorClient.getItems("Y2");
		
		assertEquals(1, resultList.size());
		assertEquals("Y2",resultList.get(0).getItemId().getProductId());
		assertEquals("A52_Supplier1",resultList.get(0).getItemId().getSupplierId());
		assertEquals(20,resultList.get(0).getPrice());
		assertEquals("Baseball",resultList.get(0).getDesc());
	}
	
	@Test
	public void getItemFromTwoSuppliers() throws InvalidItemId_Exception {
		List<ItemView> resultList = mediatorClient.getItems("X1");
		
		assertEquals(2, resultList.size());
		
		assertEquals("X1",resultList.get(0).getItemId().getProductId());
		assertEquals("A52_Supplier1",resultList.get(0).getItemId().getSupplierId());
		assertEquals(10,resultList.get(0).getPrice());
		assertEquals("Basketball",resultList.get(0).getDesc());
		
		assertEquals("X1",resultList.get(1).getItemId().getProductId());
		assertEquals("A52_Supplier2",resultList.get(1).getItemId().getSupplierId());
		assertEquals(50,resultList.get(1).getPrice());
		assertEquals("Basketball",resultList.get(1).getDesc());
	}
	
	
	// Case sensitive - tests
	@Test
	public void getItemLowercaseNotExistsTest() throws InvalidItemId_Exception {
		// product identifiers are case sensitive,
		// so "x1" is not the same as "X1"
		List<ItemView> resultList = mediatorClient.getItems("x1");
		assertEquals(0, resultList.size());
	}
	
	@Test
	public void getItemUppercaseNotExistsTest() throws InvalidItemId_Exception {
		// product identifiers are case sensitive,
		// so "Z3" is not the same as "z3"
		List<ItemView> resultList = mediatorClient.getItems("Z3");
		assertEquals(0, resultList.size());
	}
	
	@Test
	public void threeSuppliersTest() throws SupplierClientException, BadProductId_Exception, BadProduct_Exception, InvalidItemId_Exception{
		String uddiURL = testProps.getProperty("uddi.url");
		SupplierClient supplierClient3 = new SupplierClient(uddiURL, "A52_Supplier3");
		product1.setPrice(100);
		product1.setQuantity(25);
		supplierClient3.createProduct(product1);
		
		List<ItemView> resultList = mediatorClient.getItems("X1");
		
		assertEquals("X1",resultList.get(0).getItemId().getProductId());
		assertEquals("A52_Supplier1",resultList.get(0).getItemId().getSupplierId());
		assertEquals(10,resultList.get(0).getPrice());
		assertEquals("Basketball",resultList.get(0).getDesc());
		
		assertEquals("X1",resultList.get(1).getItemId().getProductId());
		assertEquals("A52_Supplier2",resultList.get(1).getItemId().getSupplierId());
		assertEquals(50,resultList.get(1).getPrice());
		assertEquals("Basketball",resultList.get(1).getDesc());
		
		assertEquals("X1",resultList.get(2).getItemId().getProductId());
		assertEquals("A52_Supplier3",resultList.get(2).getItemId().getSupplierId());
		assertEquals(100,resultList.get(2).getPrice());
		assertEquals("Basketball",resultList.get(2).getDesc());
		
	}
}
