package gr.uoc.csd.hy252;

import java.util.Date;

public class MyRestaurantTester {

	public static void main(String[] args) {
		Date d = new Date();
		Paraggelia p = new Paraggelia(d,"A18");
		p.set_persons(2);
		ServiceProduct f = new ServiceProduct(1,2);
		Product q = new Product("salata","b654",(float) 5);
		Product o = new Product("2 snitsel","b425",2*8);
		Product j = new Product("2 mpires","b123",2*3);
		p.add(f);
		p.add(q);
		p.add(o);
		p.add(j);
		System.out.println(p.ToString());
		System.out.println(p.getReceipt(p));
		System.out.println("Total price is: "+ p.getTotalPrice());
		p.delete(f);
		p.delete(q);
		p.delete(o);
		p.delete(j);
		Paraggelia k = new Paraggelia(d,"B19");
		ServiceProduct m = new ServiceProduct(1,3);
		k.set_persons(3);
		k.add(m);
		k.add(o);
		k.add(j);
		System.out.println(k.ToString());
		System.out.println(k.getReceipt(k));
		System.out.println("Total price is: "+ k.getTotalPrice());
	}

}
