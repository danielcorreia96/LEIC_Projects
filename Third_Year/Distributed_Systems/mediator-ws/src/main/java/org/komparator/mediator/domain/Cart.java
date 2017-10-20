package org.komparator.mediator.domain;

import java.util.List;

public class Cart {
	private String cartId;
	private List<CartItem> cartItems;
	
	private String getCartId() {
		return cartId;
	}
	private void setCartId(String cartId) {
		this.cartId = cartId;
	}
	private List<CartItem> getCartItems() {
		return cartItems;
	}
	private void setCartItems(List<CartItem> cartItems) {
		this.cartItems = cartItems;
	}
	
	
}
