package org.komparator.mediator.ws;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

import javax.annotation.Resource;
import javax.jws.HandlerChain;
import javax.jws.WebService;
import javax.xml.ws.WebServiceContext;
import javax.xml.ws.handler.MessageContext;

import org.komparator.mediator.domain.Item;
import org.komparator.security.handler.ServerRequestIdHandler;
import org.komparator.supplier.ws.BadProductId_Exception;
import org.komparator.supplier.ws.BadQuantity_Exception;
import org.komparator.supplier.ws.BadText_Exception;
import org.komparator.supplier.ws.InsufficientQuantity_Exception;
import org.komparator.supplier.ws.ProductView;
import org.komparator.supplier.ws.cli.SupplierClient;
import org.komparator.supplier.ws.cli.SupplierClientException;

import pt.ulisboa.tecnico.sdis.ws.cli.CreditCardClient;
import pt.ulisboa.tecnico.sdis.ws.cli.CreditCardClientException;
import pt.ulisboa.tecnico.sdis.ws.uddi.UDDINaming;
import pt.ulisboa.tecnico.sdis.ws.uddi.UDDINamingException;
import pt.ulisboa.tecnico.sdis.ws.uddi.UDDIRecord;

@WebService(
		endpointInterface = "org.komparator.mediator.ws.MediatorPortType",
		wsdlLocation = "mediator.wsdl",
		name = "MediatorWebService",
		portName = "MediatorPort",
		targetNamespace = "http://ws.mediator.komparator.org/",
		serviceName = "MediatorService"
)
@HandlerChain(file = "mediator-ws_handler-chain.xml")
public class MediatorPortImpl implements MediatorPortType {

	private static final int DELAY_TIME_FOR_TESTS = 5;
	
	// end point manager
	private MediatorEndpointManager endpointManager;
	private List<CartView> cartViewList = new ArrayList<CartView>();
	private List<ShoppingResultView> shoppingHistoryList = new ArrayList<ShoppingResultView>();
	
	private ConcurrentHashMap<String, ShoppingResultView> buyCartRequestsLog = new ConcurrentHashMap<String, ShoppingResultView>();

	private ConcurrentHashMap<String, Object> addToCartRequestsLog = new ConcurrentHashMap<String, Object>();
	
	/**
	 * Global purchase identifier counter. Uses lock-free thread-safe single
	 * variable.
	 */
	private AtomicInteger purchaseIdCounter = new AtomicInteger(0);
	// end point manager

	@Resource
	private WebServiceContext webServiceContext;
	
	public MediatorPortImpl(MediatorEndpointManager endpointManager) {
		this.endpointManager = endpointManager;
	}


	public String getCartItemSupplierID(CartItemView itemInsideTheCart) {
		return itemInsideTheCart.getItem().getItemId().getSupplierId();
	}

	public String getCartItemProductID(CartItemView itemInsideTheCart) {
		return itemInsideTheCart.getItem().getItemId().getProductId();
	}

	private SupplierClient getSupplierById(String supplierId) {
		for (SupplierClient sup :getAllSuppliers()){
			if (sup.getServiceName().equals(supplierId)){
				return sup;
			}
		}
		return null;
	}

	@Override
	public List<ShoppingResultView> shopHistory() {
		return shoppingHistoryList;
	}

	@Override
	public List<CartView> listCarts() {
		return cartViewList;
	}

	private String getCartItemSupplierId(CartItemView cartItem) {
		return getCartItemSupplierID(cartItem);
	}

	private String getCartItemProductId(CartItemView cartItem){
		return getCartItemProductID(cartItem);
	}

	private CartView getCartViewById(String cartId){
		for (CartView cartView : cartViewList) {
			if (cartView.getCartId().equals(cartId)) {
				return cartView;
			}
		}
		return null;
	}

	public SupplierClient getSupplierByName(String sid){
		UDDIRecord record;
		try {
			record = endpointManager.getUddiNaming().lookupRecord(sid);
			SupplierClient client = new SupplierClient(record.getUrl());
			client.setServiceName(record.getOrgName());
			return client;
		} catch (UDDINamingException e) {
			System.out.println("Error: couldn't reach UDDI");
		} catch (SupplierClientException e) {
			System.out.println("Error: couldn't reach Supplier");
		}
		return null;

	}

	public List<SupplierClient> getAllSuppliers(){

		List<SupplierClient> result= new ArrayList<SupplierClient>();
		UDDINaming uddi= endpointManager.getUddiNaming();

		try {
			for (UDDIRecord record: uddi.listRecords("A52_Supplier%")) {

				SupplierClient client = new SupplierClient(record.getUrl());
				client.setServiceName(record.getOrgName());
				result.add(client);
			}

		} catch (UDDINamingException | SupplierClientException e) {
			System.out.println("Error: couldn't reach UDDI or Supplier");
		}
		return result;
	}


	@Override
	public List<ItemView> getItems(String productId) throws InvalidItemId_Exception {

		System.out.println("Called getItems method looking for " + productId);
		List<ItemView> resultList = new ArrayList<ItemView>();

		try {

			for (SupplierClient client : getAllSuppliers()) {
				ProductView pview = client.getProduct(productId);    	//getProduct already checks the argument

				if (pview != null) {
					Item item = new Item(pview.getId(), client.getServiceName(), pview.getDesc(), pview.getPrice());
					resultList.add(newItemView(item));
				}

			}
		}
		catch (BadProductId_Exception e) {
			throwInvalidItemId("Invalid Product ID");
		}

		Collections.sort(resultList, new Comparator<ItemView>(){
			@Override
			public int compare(ItemView item1, ItemView item2){
				return item1.getPrice() - item2.getPrice();
			}
		});

		return resultList;
	}

	@Override
	public List<ItemView> searchItems(String descText) throws InvalidText_Exception {
		// check product id
		if (descText == null)
			throwInvalidText("Product description cannot be null!");
		descText = descText.trim();
		if (descText.length() == 0)
			throwInvalidText("Product description cannot be empty or whitespace!");

		List<SupplierClient> suppliers=getAllSuppliers();
		List<ItemView> result=new ArrayList<ItemView>();

		for (SupplierClient sup : suppliers) {
			try {
				for (ProductView pview: sup.searchProducts(descText)){
					Item item = new Item(pview.getId(), sup.getServiceName(), pview.getDesc(), pview.getPrice());
					result.add(newItemView(item));
				}
			}
			catch (BadText_Exception e) {
				throwInvalidText("Product Description invalid");
			}
		}

		Collections.sort(result, new Comparator<ItemView>(){
			@Override
			public int compare(ItemView item1, ItemView item2) {
				String name1=item1.getItemId().getProductId();
				String name2=item2.getItemId().getProductId();
				int c = name1.compareTo(name2);

				if (c==0){
					c= item1.getPrice() - item2.getPrice();
				}
				return c;
			}
		});
		return result;
	}


	@Override
	public synchronized ShoppingResultView buyCart(String cartId, String creditCardNr)
			throws EmptyCart_Exception, InvalidCartId_Exception, InvalidCreditCard_Exception {

		String clientRequestId = getRequestIdFromMessageContext();
		
		if(buyCartRequestsLog.containsKey(clientRequestId)){
			System.out.printf("\nja tenho este token \n");
			return buyCartRequestsLog.get(clientRequestId);
		}

		if(cartId==null || !cartId.matches("[A-Za-z0-9]+")){
			throwInvalidCartId("cartId not valid.");
		}
		
		CartView targetCart = getCartViewById(cartId);
		if (targetCart == null) {
			throwInvalidCartId("No existing cart for the given cartId - " + cartId);
		}

		if (validateCreditCardNumber(creditCardNr) == false) {
			throwInvalidCreditCard("Error: invalid credit card number or validation process failed");
		}

		ShoppingResultView shopRes = new ShoppingResultView();
		shopRes.setId(generateShoppingId(cartId));
		int totalPrice = 0;

		for (CartItemView cartItem : targetCart.getItems()) {

			String productId = getCartItemProductId(cartItem);
			SupplierClient supplierClient= getSupplierByName(getCartItemSupplierId(cartItem));

				try {
					String purchaseConfirmation = supplierClient.buyProduct(productId, cartItem.getQuantity());
					System.out.println("Purchase confirmation: " + purchaseConfirmation);

					totalPrice +=  supplierClient.getProduct(productId).getPrice() * cartItem.getQuantity();
					shopRes.getPurchasedItems().add(cartItem);


				} catch (BadProductId_Exception | BadQuantity_Exception | InsufficientQuantity_Exception e) {
					System.out.println("Adding to dropped items: Not enough quantity of product with id " + productId + " at supplier " + getCartItemSupplierId(cartItem));
					shopRes.getDroppedItems().add(cartItem);
				}
		}

		shopRes.setResult(getShoppingResult(shopRes.getPurchasedItems(), shopRes.getDroppedItems()));
		shopRes.setTotalPrice(totalPrice);
		shoppingHistoryList.add(0, shopRes);
		
		clientRequestId = getRequestIdFromMessageContext();
		buyCartRequestsLog.put(clientRequestId, shopRes);
		LifeProof.client.updateShopHistory(shopRes, clientRequestId);
		
		delayServerForTests();
		
		return shopRes;	
	}

	private void delayServerForTests() {
		try {
			System.out.printf("%d segundos de espera, caso queiras parar o servidor%n", DELAY_TIME_FOR_TESTS);
			TimeUnit.SECONDS.sleep(DELAY_TIME_FOR_TESTS);
		} catch (InterruptedException e) {
			System.out.println("sleep was interrupted in delayServer method");
		}
	}

	private String getRequestIdFromMessageContext() {
		MessageContext messageContext;
		String propertyValue;
		// retrieve message context
		messageContext = webServiceContext.getMessageContext();

		// get token from message context
		propertyValue = (String) messageContext.get(ServerRequestIdHandler.REQUEST_PROPERTY);
		System.out.printf("\ngot token '%s' from response context%n \n", propertyValue);
		return propertyValue;
	}

	private String generateShoppingId(String cartId) {
		// relying on AtomicInteger to make sure assigned number is unique
		int purchaseId = purchaseIdCounter.incrementAndGet();
		return cartId + Integer.toString(purchaseId);
	}

	private Result getShoppingResult(List<CartItemView> purchasedItems, List<CartItemView> nonPurchasedItems) {
		if (nonPurchasedItems.size() == 0) {
			return Result.COMPLETE;
		}
		else if (purchasedItems.size() == 0) {
			return Result.EMPTY;
		}
		else if (nonPurchasedItems.size() > 0 && purchasedItems.size() > 0) {
			return Result.PARTIAL;
		}
		return null;
	}


	private boolean validateCreditCardNumber(String creditCardNumber){
		try {
			// 1. Get CC Web Service URL
			String creditCard_wsURL = endpointManager.getUddiNaming().lookup("CreditCard");

			// 2. Create CC Web Service Client
			CreditCardClient creditCardValidator = new CreditCardClient(creditCard_wsURL);

			// 3. Validate credit card number
			return creditCardValidator.validateNumber(creditCardNumber);

		} catch (UDDINamingException e) {
			System.out.println("Error: couldn't reach UDDI server");
		} catch (CreditCardClientException e) {
			System.out.println("Error: couldn't create a credit card client");
		}
		return false;
	}

	@Override
	public void addToCart(String cartId, ItemIdView itemId, int itemQty) throws InvalidCartId_Exception,
			InvalidItemId_Exception, InvalidQuantity_Exception, NotEnoughItems_Exception {

		String clientRequestId = getRequestIdFromMessageContext();
		
		if(addToCartRequestsLog.containsKey(clientRequestId)){
			System.out.printf("\n(addCart)ja tenho este token \n");
			return;
		}

		if(cartId==null || !cartId.matches("[A-Za-z0-9]+"))
			throwInvalidCartId("cartId not valid.");

		if(itemId==null)
			throwInvalidItemId("itemIdView not valid.");
		
		if(itemQty<=0)
			throwInvalidQuantity("Item quantity must be positive.");

		SupplierClient sup = getSupplierById(itemId.getSupplierId());

		if (sup==null)
			throwInvalidItemId("itemId Supplier Doesn't Exist");

		ProductView productView=null;

		synchronized(this){
			
			try {
				productView = sup.getProduct(itemId.getProductId());
			}
			catch (BadProductId_Exception e) {
				throwInvalidItemId("itemId Product Doesn't Exist");
			}


			if(productView==null)
				throwInvalidItemId("Product Not Found");

			if(productView.getQuantity()<itemQty)
				throwNotEnoughItems("Adding more than what exists");

			Item item = new Item(productView.getId(), sup.getServiceName(), productView.getDesc(), productView.getPrice());
			ItemView itemView=newItemView(item);
			CartItemView cartItemview = newCartItemView(itemView,itemQty);


			for(CartView cartView: this.listCarts()){
				if (cartView.getCartId().equals(cartId)){

					for (CartItemView cItemView:cartView.getItems()){

						if (getCartItemProductID(cItemView).equals(itemId.getProductId()) && getCartItemSupplierID(cItemView).equals(itemId.getSupplierId())){

							if(productView.getQuantity()<itemQty+cItemView.getQuantity()){
								throwNotEnoughItems("The Quantity you are adding plus what you already ordered exceed the available");
							}
							
							cItemView.setQuantity(cItemView.getQuantity()+itemQty);
							
							clientRequestId = getRequestIdFromMessageContext();
							addToCartRequestsLog.put(clientRequestId, cartView);
							LifeProof.client.updateCart(cartView, clientRequestId);
							delayServerForTests();
							
							return;/*added the quantity so exit*/
						}
					}
					cartView.getItems().add(cartItemview);
					clientRequestId = getRequestIdFromMessageContext();
					addToCartRequestsLog.put(clientRequestId, cartView);
					LifeProof.client.updateCart(cartView, clientRequestId);
					
					delayServerForTests();
					
					return;/*Added new Item to the Cart so exit*/

				}

				//endsync}
			}

			/*if cart doesn't Exist*/

			CartView newCart=newCartView(cartId);
			newCart.getItems().add(cartItemview);
			cartViewList.add(newCart);
			
			clientRequestId = getRequestIdFromMessageContext();
			addToCartRequestsLog.put(clientRequestId, newCart);
			LifeProof.client.updateCart(newCart, clientRequestId);
			delayServerForTests();
			
			return;/*Created new Cart and put Item in it*/
		}
	}

	@Override
	public String ping(String arg0) {
   	 	String result = "";
   	 	for (SupplierClient client : getAllSuppliers()) {
   	 		result += client.ping(arg0) + "\n";
   	 	}
   	 	System.out.println(result);
		return result;
	}



	// Main operations -------------------------------------------------------



	// Auxiliary operations --------------------------------------------------



	// View helpers -----------------------------------------------------

	private ItemView newItemView(Item item) {
		ItemIdView idview = new ItemIdView();
		idview.setSupplierId(item.getSupplierId());
		idview.setProductId(item.getProductId());

		ItemView view = new ItemView();
		view.setItemId(idview);
		view.setDesc(item.getDescription());
		view.setPrice(item.getPrice());
		return view;
	}

	private CartItemView newCartItemView(ItemView cartItem,int itemQty){
		CartItemView cartItemView= new CartItemView();
		cartItemView.setItem(cartItem);
		cartItemView.setQuantity(itemQty);
		return cartItemView;
	}

    private CartView newCartView(String cartId){
    	CartView cartView = new CartView();
    	cartView.setCartId(cartId);
    	return cartView;
    }


	// Exception helpers -----------------------------------------------------

	private void throwInvalidItemId(String message) throws InvalidItemId_Exception {
		InvalidItemId faultInfo = new InvalidItemId();
		faultInfo.message = message;
		throw new InvalidItemId_Exception(message, faultInfo);
	}

	private void throwInvalidText(String message) throws InvalidText_Exception {
		InvalidText faultInfo = new InvalidText();
		faultInfo.message=message;
		throw new InvalidText_Exception(message, faultInfo);
	}

	private void throwInvalidCreditCard(String message) throws InvalidCreditCard_Exception {
		InvalidCreditCard faultInfo = new InvalidCreditCard();
		faultInfo.message = message;
		throw new InvalidCreditCard_Exception(message, faultInfo);

	}

	private void throwInvalidCartId(String message) throws InvalidCartId_Exception {
		InvalidCartId faultInfo = new InvalidCartId();
		faultInfo.message=message;
		throw new InvalidCartId_Exception(message, faultInfo);
	}

	private void throwNotEnoughItems(String message) throws NotEnoughItems_Exception{
		NotEnoughItems faultInfo = new NotEnoughItems();
		faultInfo.message=message;
		throw new NotEnoughItems_Exception(message, faultInfo);
	}

	private void throwInvalidQuantity(String message) throws InvalidQuantity_Exception{
		InvalidQuantity faultInfo = new InvalidQuantity();
		faultInfo.message=message;
		throw new InvalidQuantity_Exception(message, faultInfo);
	}


	@Override
	public void clear() {
		cartViewList.clear();
		for (SupplierClient sup: getAllSuppliers())
			sup.clear();
	}
	
	@Override
	public void imAlive(){
		if (this.endpointManager.isPrimary()){
			return;
		}
		LifeProof.lastLifeProof=new Date();
		
	}


	@Override
	public void updateShopHistory(ShoppingResultView shopResult, String clientRequestId) {
		if(!this.endpointManager.isPrimary()){
			System.out.println("sou o secundario no updateShopHistory");
			System.out.println("Pre update: " + this.shopHistory().size() );
			shoppingHistoryList.add(0, shopResult);
			System.out.println("Pos update: " + this.shopHistory().size() );
			buyCartRequestsLog.put(clientRequestId, shopResult);
		}
		// sou o primario, isto nao devia chegar aqui...
	}


	@Override
	public void updateCart(CartView cart, String clientRequestId) {
		if(!this.endpointManager.isPrimary()){
			System.out.println("sou o secundario no updateCart");
			for(CartView cartView: this.listCarts()){
				if (cartView.getCartId().equals(cart.getCartId())){
					System.out.println("Pre remove: "+this.listCarts().size() );
					this.listCarts().remove(cartView);
					System.out.println("Pos remove: "+this.listCarts().size() );
					break;
				}
			}
			System.out.println("Pre update: " + this.listCarts().size() );
			cartViewList.add(cart);
			addToCartRequestsLog.put(clientRequestId, cart);
			System.out.println("Pos update: " + this.listCarts().size() );
		}
		// sou o primario, isto nao devia chegar aqui...
	}

}
