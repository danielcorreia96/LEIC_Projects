package org.komparator.mediator.domain;

public class Item {
	private String productId;
    private String supplierId;
    private String description;
    private int price;
    
    public Item(String pid, String sid, String description, int price){
    	this.productId = pid;
    	this.supplierId = sid;
    	this.description = description;
    	this.price = price;
    }
	public int getPrice() {
		return price;
	}
	public void setPrice(int price) {
		this.price = price;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String desc) {
		this.description = desc;
	}
	public String getSupplierId() {
		return supplierId;
	}
	public void setSupplierId(String supplierId) {
		this.supplierId = supplierId;
	}
	public String getProductId() {
		return productId;
	}
	public void setProductId(String productId) {
		this.productId = productId;
	}
}
