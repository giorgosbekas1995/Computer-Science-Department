package gr.uoc.csd.hy252;

public class Product {
private String name;
private String barCode;
private float price;


public Product(String name,String barCode,float price){
	this.name=name;
	this.barCode=barCode;
	this.price=price;
}

public Product(){}



public String ToString(){
	return name + " " +barCode+ " " +getPrice();
}

public float getPrice() {
	return price;
}

public String getName() {
	return name;
}

public String getBarcode() {
	return barCode;
}

}

