package org.komparator.mediator.ws.it;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.komparator.mediator.ws.InvalidCartId_Exception;
import org.komparator.mediator.ws.InvalidItemId_Exception;
import org.komparator.mediator.ws.InvalidQuantity_Exception;
import org.komparator.mediator.ws.ItemIdView;
import org.komparator.mediator.ws.NotEnoughItems_Exception;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadProduct_Exception;
import org.komparator.supplier.ws.ProductView;


public class AddToCartIT extends BaseIT {
	
	private static final String CARTID = "Carrinho";
	private static ItemIdView ITEMIDVIEW;
	static ProductView product1;
	static ProductView product2;
	static ProductView product3;
	@Before
	public void oneTimeSetUp() throws BadProductId_Exception, BadProduct_Exception {
		mediatorClient.clear();
		product1 = new ProductView();
		product1.setId("X1");
		product1.setDesc("Basketball");
		product1.setPrice(10);
		product1.setQuantity(10);

		product2 = new ProductView();
		product2.setId("Y2");
		product2.setDesc("Baseball");
		product2.setPrice(20);
		product2.setQuantity(20);

		product3 = new ProductView();
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
		ITEMIDVIEW = new ItemIdView();
		ITEMIDVIEW.setProductId(product1.getId());
		ITEMIDVIEW.setSupplierId(supplierClient1.getServiceName());
		
		
		
		
	}
	
	@After
	public void tearDown(){
		mediatorClient.clear();
	}
	
	//Bad CardId Tests
	@Test(expected=InvalidCartId_Exception.class)
	public void InvalidCartIdNull() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart(null, AddToCartIT.ITEMIDVIEW, 5);
	}
	
	
	@Test(expected=InvalidCartId_Exception.class)
	public void InvalidCartIdEmpty() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart("", ITEMIDVIEW, 5);
	}
	
	
	@Test(expected=InvalidCartId_Exception.class)
	public void InvalidCartIdWhiteSpace() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart("     ", ITEMIDVIEW, 5);
	}

	
	@Test(expected=InvalidCartId_Exception.class)
	public void InvalidCartIdMiddleWhiteSpace() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart("X 1", ITEMIDVIEW, 5);
	}
	
	@Test(expected=InvalidCartId_Exception.class)
	public void InvalidCartIdHasTabs() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart("X1\t", ITEMIDVIEW, 5);
	}
	
	
	@Test(expected=InvalidCartId_Exception.class)
	public void InvalidCartIdHasPoint() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart("X1.", ITEMIDVIEW, 5);
		
	}
	
	@Test(expected=InvalidCartId_Exception.class)
	public void InvalidCartIdHasNewLine() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart("X1\n", ITEMIDVIEW, 5);
		
	}
	
	
	@Test
	public void successCartLowerAndHigherCase() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart("x1", ITEMIDVIEW, 5);
		mediatorClient.addToCart("X1", ITEMIDVIEW, 5);
		assertEquals(2, mediatorClient.listCarts().size());
		
	}
	
	
	@Test(expected=InvalidItemId_Exception.class)
	public void InvalidItemIdNull() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart(CARTID, null, 5);
	}
	
	
	@Test(expected=InvalidItemId_Exception.class)
	public void InvalidItemIdIncorrectServiceId() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		
		ItemIdView itemIdViewIncorrectServiceId= new ItemIdView();
		itemIdViewIncorrectServiceId.setProductId(product1.getId());
		itemIdViewIncorrectServiceId.setSupplierId("IDONTEXIST");
		mediatorClient.addToCart(CARTID, itemIdViewIncorrectServiceId, 5);
	}
	
	
	@Test(expected=InvalidItemId_Exception.class)
	public void InvalidItemIdIncorrectProductId() throws InvalidCartId_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		
		ItemIdView itemIdViewIncorrectProductId= new ItemIdView();
		itemIdViewIncorrectProductId.setProductId("L");
		itemIdViewIncorrectProductId.setSupplierId(supplierClient1.getServiceName());
		mediatorClient.addToCart(CARTID, itemIdViewIncorrectProductId, 5);
	}
	
	
	@Test(expected=InvalidQuantity_Exception.class)
	public void quantityNegative() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		
		mediatorClient.addToCart(CARTID,ITEMIDVIEW, -5);
	}
	@Test(expected=InvalidQuantity_Exception.class)
	public void quantityZero() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		
		mediatorClient.addToCart(CARTID,ITEMIDVIEW, 0);
	}
	
	@Test(expected=NotEnoughItems_Exception.class)
	public void quantityTooMuch() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		
		mediatorClient.addToCart(CARTID,ITEMIDVIEW, 11);
	}
	
	
	@Test(expected=NotEnoughItems_Exception.class)
	public void quantityTooMuchOnLaterAdd() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		
		mediatorClient.addToCart(CARTID,ITEMIDVIEW, 9);
		mediatorClient.addToCart(CARTID,ITEMIDVIEW, 2);
	}
	
	
	@Test
	public void successWithMaxQuantity() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,10);
		assertEquals(1,mediatorClient.listCarts().size());
		assertEquals(CARTID,mediatorClient.listCarts().get(0).getCartId());
		assertEquals(10,mediatorClient.listCarts().get(0).getItems().get(0).getQuantity());


	}
	
	@Test
	public void successAddToSameCartSameProduct() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,5);
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,2);
		assertEquals(1,mediatorClient.listCarts().size());
		assertEquals(CARTID,mediatorClient.listCarts().get(0).getCartId());
		assertEquals(7,mediatorClient.listCarts().get(0).getItems().get(0).getQuantity());
		
	}
	
	
	@Test
	public void successAddToSameCartDifferentProduct() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,5);
		ITEMIDVIEW.setProductId(product2.getId());
		ITEMIDVIEW.setSupplierId(supplierClient1.getServiceName());
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,2);
		
		assertEquals(1,mediatorClient.listCarts().size());
		assertEquals(CARTID,mediatorClient.listCarts().get(0).getCartId());
		assertEquals(2,mediatorClient.listCarts().get(0).getItems().size());
		assertEquals(5,mediatorClient.listCarts().get(0).getItems().get(0).getQuantity());
		assertEquals(2,mediatorClient.listCarts().get(0).getItems().get(1).getQuantity());
		
	}
	
	
	@Test
	public void successAddToSameCartDifferentSupplier() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		ItemIdView itemIdView2= new ItemIdView();
		itemIdView2.setProductId(product2.getId());
		itemIdView2.setSupplierId(supplierClient1.getServiceName());
		
		
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,5);
		ITEMIDVIEW.setProductId(product2.getId());
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,2);
		
		assertEquals(1,mediatorClient.listCarts().size());
		assertEquals(CARTID,mediatorClient.listCarts().get(0).getCartId());
		assertEquals(2,mediatorClient.listCarts().get(0).getItems().size());
		assertEquals(5,mediatorClient.listCarts().get(0).getItems().get(0).getQuantity());
		assertEquals(2,mediatorClient.listCarts().get(0).getItems().get(1).getQuantity());
		
	}
	
	
	@Test
	public void successAddToDifferentCartSameProduct() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		
		
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,5);
		mediatorClient.addToCart("Carrinho2",ITEMIDVIEW,5);
		
		assertEquals(2,mediatorClient.listCarts().size());
		assertEquals(CARTID,mediatorClient.listCarts().get(0).getCartId());
		assertEquals("Carrinho2",mediatorClient.listCarts().get(1).getCartId());
		assertEquals(1,mediatorClient.listCarts().get(0).getItems().size());
		assertEquals(1,mediatorClient.listCarts().get(1).getItems().size());
	}
	
	@Test
	public void successAllItemsIn2DifferentCarts2DifferentSuppliers() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		
		
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,5);
		mediatorClient.addToCart("Carrinho2",ITEMIDVIEW,5);
		
		ITEMIDVIEW.setProductId(product2.getId());
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,10);
		mediatorClient.addToCart("Carrinho2",ITEMIDVIEW,10);
		
		ITEMIDVIEW.setProductId(product3.getId());
		ITEMIDVIEW.setSupplierId(supplierClient2.getServiceName());
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,15);
		mediatorClient.addToCart("Carrinho2",ITEMIDVIEW,15);
		
		ITEMIDVIEW.setProductId(product1.getId());
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,5);
		mediatorClient.addToCart("Carrinho2",ITEMIDVIEW,5);
		
		assertEquals(2,mediatorClient.listCarts().size());
		assertEquals(4,mediatorClient.listCarts().get(0).getItems().size());
		assertEquals(4,mediatorClient.listCarts().get(1).getItems().size());
	}
	
	@Test
	public void successSimpleCartCreation() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception{
		if(verbose){
			System.out.println("Testing " + Thread.currentThread().getStackTrace()[1].getMethodName());
		}
		mediatorClient.addToCart(CARTID,ITEMIDVIEW,1);
		assertFalse(mediatorClient.listCarts().isEmpty());
		assertEquals(ITEMIDVIEW.getProductId(),mediatorClient.listCarts().get(0).getItems().get(0).getItem().getItemId().getProductId());
		assertEquals(ITEMIDVIEW.getSupplierId(),mediatorClient.listCarts().get(0).getItems().get(0).getItem().getItemId().getSupplierId());
		assertEquals(1,mediatorClient.listCarts().get(0).getItems().get(0).getQuantity());
	}
	
}
