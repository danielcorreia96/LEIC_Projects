package org.komparator.mediator.ws.it;

import static org.junit.Assert.assertEquals;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.komparator.mediator.ws.EmptyCart_Exception;
import org.komparator.mediator.ws.InvalidCartId_Exception;
import org.komparator.mediator.ws.InvalidCreditCard_Exception;
import org.komparator.mediator.ws.InvalidItemId_Exception;
import org.komparator.mediator.ws.InvalidQuantity_Exception;
import org.komparator.mediator.ws.ItemIdView;
import org.komparator.mediator.ws.NotEnoughItems_Exception;
import org.komparator.mediator.ws.Result;
import org.komparator.mediator.ws.ShoppingResultView;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadProduct_Exception;
import org.komparator.supplier.ws.ProductView;

public class BuyCartIT extends BaseIT {
	private static final String VALID_CREDITCARD_NUMBER = "4024007102923926";

	static ItemIdView ITEMIDVIEWCORRECT;
	
	static ProductView product1;
	static ProductView product2;
	static ProductView product3;
	@Before
	public void fillSuppliersSetUp() throws BadProductId_Exception, BadProduct_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {
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
		
		ITEMIDVIEWCORRECT = new ItemIdView();
		ITEMIDVIEWCORRECT.setProductId(product1.getId());
		ITEMIDVIEWCORRECT.setSupplierId(supplierClient1.getServiceName());
		mediatorClient.addToCart("cart1", ITEMIDVIEWCORRECT, 10);
	}
	
	

	@After
	public void tearDown(){
		mediatorClient.clear();
	}
	
	// Credit card validation tests
	@Test(expected=InvalidCreditCard_Exception.class)
	public void invalidCreditCardNumber() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception {
		mediatorClient.buyCart("cart1", "123456789");
	}
	
	// Bad cartId input tests
	@Test(expected=InvalidCartId_Exception.class)
	public void nullCardIdTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart(null, VALID_CREDITCARD_NUMBER);
	}
	
	@Test(expected = InvalidCartId_Exception.class)
	public void getItemsEmptyTest() throws InvalidCartId_Exception, EmptyCart_Exception, InvalidCreditCard_Exception {
		mediatorClient.buyCart("", VALID_CREDITCARD_NUMBER);
	}

	@Test(expected = InvalidCartId_Exception.class)
	public void getItemsWhitespaceTest() throws InvalidCartId_Exception, EmptyCart_Exception, InvalidCreditCard_Exception {
		mediatorClient.buyCart(" ", VALID_CREDITCARD_NUMBER);
	}

	@Test(expected = InvalidCartId_Exception.class)
	public void getItemsTabTest() throws InvalidCartId_Exception, EmptyCart_Exception, InvalidCreditCard_Exception {
		mediatorClient.buyCart("\t", VALID_CREDITCARD_NUMBER);
	}

	@Test(expected = InvalidCartId_Exception.class)
	public void getItemsNewlineTest() throws InvalidCartId_Exception, EmptyCart_Exception, InvalidCreditCard_Exception {
		mediatorClient.buyCart("\n", VALID_CREDITCARD_NUMBER);
	}

	@Test(expected = InvalidCartId_Exception.class)
	public void getItemsPointTest() throws InvalidCartId_Exception, EmptyCart_Exception, InvalidCreditCard_Exception {
		mediatorClient.buyCart(".X1", VALID_CREDITCARD_NUMBER);
	}

	@Test(expected = InvalidCartId_Exception.class)
	public void getItemsUnderscoreTest() throws InvalidCartId_Exception, EmptyCart_Exception, InvalidCreditCard_Exception {
		mediatorClient.buyCart("_X1", VALID_CREDITCARD_NUMBER);
	}

	@Test(expected = InvalidCartId_Exception.class)
	public void getItemsMiddlespaceTest() throws InvalidCartId_Exception, EmptyCart_Exception, InvalidCreditCard_Exception{
		mediatorClient.buyCart("X 1", VALID_CREDITCARD_NUMBER);
	}
	
	// BuyCart simple tests - only one cart	
	
	// 1. COMPLETE result tests
	@Test
	public void completeBuyOneItemOneCartTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception, BadProductId_Exception{	
		ShoppingResultView result = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());
		
		// check shopping result
		System.out.println("teste print:    " + result);
		assertEquals(100, result.getTotalPrice());
		assertEquals(Result.COMPLETE, result.getResult());
		assertEquals(1, result.getPurchasedItems().size());
		assertEquals(0, result.getDroppedItems().size());
	}
	
	@Test
	public void completeBuyTwoItemsOneCartTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception, BadProductId_Exception{
		ItemIdView item = new ItemIdView();
		item.setProductId(product2.getId());
		item.setSupplierId(supplierClient1.getServiceName());
		mediatorClient.addToCart("cart1", item, 20);
		
		ShoppingResultView result = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());
		assertEquals(0,  supplierClient1.getProduct("Y2").getQuantity());

		// check shopping result
		assertEquals(500, result.getTotalPrice());
		assertEquals(Result.COMPLETE, result.getResult());
		assertEquals(2, result.getPurchasedItems().size());
		assertEquals(0, result.getDroppedItems().size());
	}
	
	// 2. PARTIAL result tests
	@Test
	public void partialBuyTwoItemsOneCartTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception, BadProductId_Exception{
		ItemIdView item = new ItemIdView();
		item.setProductId(product2.getId());
		item.setSupplierId(supplierClient1.getServiceName());
		mediatorClient.addToCart("cart1", item, 10);
		
		ShoppingResultView firstBuyResult = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());
		assertEquals(10,  supplierClient1.getProduct("Y2").getQuantity());

		// check shopping result
		assertEquals(300, firstBuyResult.getTotalPrice());
		assertEquals(Result.COMPLETE, firstBuyResult.getResult());
		assertEquals(2, firstBuyResult.getPurchasedItems().size());
		assertEquals(0, firstBuyResult.getDroppedItems().size());
		
		ShoppingResultView secondBuyResult = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());
		assertEquals(0,  supplierClient1.getProduct("Y2").getQuantity());

		// check shopping result
		assertEquals(200, secondBuyResult.getTotalPrice());
		assertEquals(Result.PARTIAL, secondBuyResult.getResult());
		assertEquals(1, secondBuyResult.getPurchasedItems().size());
		assertEquals(1, secondBuyResult.getDroppedItems().size());
	}
	
	// 3. EMPTY result tests
	@Test
	public void emptyBuyOneItemOneCartTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception, BadProductId_Exception{		
		ShoppingResultView firstBuyResult = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());

		// check shopping result
		assertEquals(100, firstBuyResult.getTotalPrice());
		assertEquals(Result.COMPLETE, firstBuyResult.getResult());
		assertEquals(1, firstBuyResult.getPurchasedItems().size());
		assertEquals(0, firstBuyResult.getDroppedItems().size());
		
		ShoppingResultView secondBuyResult = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());

		// check shopping result
		assertEquals(0, secondBuyResult.getTotalPrice());
		assertEquals(Result.EMPTY, secondBuyResult.getResult());
		assertEquals(0, secondBuyResult.getPurchasedItems().size());
		assertEquals(1, secondBuyResult.getDroppedItems().size());
	}
	
	@Test
	public void emptyBuyTwoItemsOneCartTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception, BadProductId_Exception{
		ItemIdView item = new ItemIdView();
		item.setProductId(product2.getId());
		item.setSupplierId(supplierClient1.getServiceName());
		mediatorClient.addToCart("cart1", item, 20);
		ShoppingResultView firstBuyResult = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
	
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());
		assertEquals(0,  supplierClient1.getProduct("Y2").getQuantity());

		// check shopping result
		assertEquals(500, firstBuyResult.getTotalPrice());
		assertEquals(Result.COMPLETE, firstBuyResult.getResult());
		assertEquals(2, firstBuyResult.getPurchasedItems().size());
		assertEquals(0, firstBuyResult.getDroppedItems().size());
	
		ShoppingResultView secondBuyResult = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());

		// check shopping result
		assertEquals(0, secondBuyResult.getTotalPrice());
		assertEquals(Result.EMPTY, secondBuyResult.getResult());
		assertEquals(0, secondBuyResult.getPurchasedItems().size());
		assertEquals(2, secondBuyResult.getDroppedItems().size());
	}
	
	
	// BuyCart tests with 2+ carts
	
	// 1. COMPLETE result tests
	@Test
	public void completeBuyOneItemTwoCartsTests() throws BadProductId_Exception, BadProduct_Exception, InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception, EmptyCart_Exception, InvalidCreditCard_Exception{
		// product 1 in supplier 1 has quantity 20 and price 10 in this test
		product1.setPrice(10);
		product1.setQuantity(20);
		supplierClient1.createProduct(product1);
		mediatorClient.addToCart("cart2", ITEMIDVIEWCORRECT, 10);
		// two carts each buying 10 pieces of product in supplier 1 (which has 20 pieces)
		ShoppingResultView firstCartResult = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		ShoppingResultView secondCartResult = mediatorClient.buyCart("cart2", VALID_CREDITCARD_NUMBER);
		
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());
		
		// check shopping results - both should be COMPLETE
		assertEquals(100, firstCartResult.getTotalPrice());
		assertEquals(100, secondCartResult.getTotalPrice());

		assertEquals(Result.COMPLETE, firstCartResult.getResult());
		assertEquals(Result.COMPLETE, secondCartResult.getResult());
		
		assertEquals(1, firstCartResult.getPurchasedItems().size());
		assertEquals(1, secondCartResult.getPurchasedItems().size());
		
		assertEquals(0, firstCartResult.getDroppedItems().size());
		assertEquals(0, secondCartResult.getDroppedItems().size());
	}
	
	// 2. PARTIAL result tests
	@Test
	public void partialBuyTwoItemsTwoCartsTest() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception, EmptyCart_Exception, InvalidCreditCard_Exception, BadProductId_Exception{
		// caso de teste: 2 carts com 2 items com um item em comum. o segundo cart ja nao consegue comprar o item comum e da PARTIAL
		ItemIdView item2_s1 = new ItemIdView();
		item2_s1.setProductId(product2.getId());
		item2_s1.setSupplierId(supplierClient1.getServiceName());
		
		ItemIdView item2_s2 = new ItemIdView();
		item2_s2.setProductId(product3.getId());
		item2_s2.setSupplierId(supplierClient2.getServiceName());
		
		mediatorClient.addToCart("cart1", item2_s1, 20);
		mediatorClient.addToCart("cart2", item2_s2, 30);
		// adicionar item comum ao segundo cart
		mediatorClient.addToCart("cart2", ITEMIDVIEWCORRECT, 10);
		
		ShoppingResultView firstCartResult = mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		ShoppingResultView secondCartResult = mediatorClient.buyCart("cart2", VALID_CREDITCARD_NUMBER);
		
		// check updated suppliers
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());
		assertEquals(0,  supplierClient1.getProduct("Y2").getQuantity());
		assertEquals(0,  supplierClient2.getProduct("z3").getQuantity());
		
		// check shopping results
		assertEquals(500, firstCartResult.getTotalPrice());
		assertEquals(900, secondCartResult.getTotalPrice());

		assertEquals(Result.COMPLETE, firstCartResult.getResult());
		assertEquals(Result.PARTIAL, secondCartResult.getResult());
		
		assertEquals(2, firstCartResult.getPurchasedItems().size());
		assertEquals(1, secondCartResult.getPurchasedItems().size());
		
		assertEquals(0, firstCartResult.getDroppedItems().size());
		assertEquals(1, secondCartResult.getDroppedItems().size());
	}
	
	// 3. EMPTY result tests
	@Test
	public void emptyBuyTwoItemsTwoCartsTest() throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception, BadProductId_Exception{
		// caso de teste: comprar o primeiro cart esgota os produtos necessarios para comprar o segundo cart
		mediatorClient.addToCart("cart2", ITEMIDVIEWCORRECT, 10);
		
		ShoppingResultView firstCartResult =  mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		ShoppingResultView secondCartResult = mediatorClient.buyCart("cart2", VALID_CREDITCARD_NUMBER);
		
		// check updated supplier
		assertEquals(0,  supplierClient1.getProduct("X1").getQuantity());
		
		// check shopping results
		assertEquals(100, firstCartResult.getTotalPrice());
		assertEquals(0, secondCartResult.getTotalPrice());

		assertEquals(Result.COMPLETE, firstCartResult.getResult());
		assertEquals(Result.EMPTY, secondCartResult.getResult());
		
		assertEquals(1, firstCartResult.getPurchasedItems().size());
		assertEquals(0, secondCartResult.getPurchasedItems().size());
		
		assertEquals(0, firstCartResult.getDroppedItems().size());
		assertEquals(1, secondCartResult.getDroppedItems().size());
		
	}
	
	@Test
	public void emptyAfterPartialBuyTwoItemsThreeCartsTest() throws InvalidCartId_Exception, InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception, EmptyCart_Exception, InvalidCreditCard_Exception, BadProductId_Exception{
		// caso de teste
		// 		primeiro buy: compra cart1 e da COMPLETE (compra 10 de product1)
		//		segundo buy: compra cart2 e da PARTIAL (compra de 20 product2 e nao consegue comprar 10 de product1)
		// 		terceiro buy: compra cart3 e da EMPTY porque tem um item comum com o cart2 (nao consegue comprar 10 de product1)
		ItemIdView item2_s1 = new ItemIdView();
		item2_s1.setProductId(product2.getId());
		item2_s1.setSupplierId(supplierClient1.getServiceName());
		
		mediatorClient.addToCart("cart2", item2_s1, 20);
		mediatorClient.addToCart("cart2", ITEMIDVIEWCORRECT, 10);
		mediatorClient.addToCart("cart3", ITEMIDVIEWCORRECT, 10);
		
		ShoppingResultView firstCartResult =  mediatorClient.buyCart("cart1", VALID_CREDITCARD_NUMBER);
		ShoppingResultView secondCartResult = mediatorClient.buyCart("cart2", VALID_CREDITCARD_NUMBER);
		ShoppingResultView thirdCartResult =  mediatorClient.buyCart("cart3", VALID_CREDITCARD_NUMBER);
		
		// check updated supplier
		assertEquals(0,supplierClient1.getProduct("X1").getQuantity());
		assertEquals(0,supplierClient1.getProduct("Y2").getQuantity());
		
		// check shopping results
		assertEquals(100, firstCartResult.getTotalPrice());
		assertEquals(400, secondCartResult.getTotalPrice());
		assertEquals(0, thirdCartResult.getTotalPrice());

		assertEquals(Result.COMPLETE, firstCartResult.getResult());
		assertEquals(Result.PARTIAL, secondCartResult.getResult());
		assertEquals(Result.EMPTY, thirdCartResult.getResult());
		
		assertEquals(1, firstCartResult.getPurchasedItems().size());
		assertEquals(1, secondCartResult.getPurchasedItems().size());
		assertEquals(0, thirdCartResult.getPurchasedItems().size());
		
		assertEquals(0, firstCartResult.getDroppedItems().size());
		assertEquals(1, secondCartResult.getDroppedItems().size());
		assertEquals(1, secondCartResult.getDroppedItems().size());
	}
}
