package gr.uoc.csd.hy252;

public class ServiceProduct extends Product {
	private String name="κουβέρ";
	private String barCode="b001";
	private float price;
	private int people;


ServiceProduct(){}

ServiceProduct(float price,int people){
	this.price=price;
	this.people=people;
}


public String ToString(){
	return name+ " " +barCode+ " " + price + " " + people;
}

public String getName() {
	return name;
}

public String getBarcode() {
	return barCode;
}

public float getPrice() {
	return price*people;
}

}