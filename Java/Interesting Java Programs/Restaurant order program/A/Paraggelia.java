package gr.uoc.csd.hy252;

import java.util.ArrayList;
import java.util.Date;


public class Paraggelia {
private  Date date;
private String table_number;
private int persons;



static ArrayList<Product> c = new ArrayList<Product>();


public Paraggelia(Date date,String tnum){
	this.date=date;
	table_number=tnum;
}
public Paraggelia() {
	
}

public String getTablenumber(){
	return table_number;
}

public String ToString(){
	return "date: " +date + "\n" + "table: " + table_number + "\n" + "persons: " + persons;
	
}

public void set_or_change(String new_table){
	table_number=new_table;
}

public void set_persons(int persons){
	this.persons=persons;
}
 public void add (Product p){
	 c.add(p);
}

public void delete(Product p){
	 c.remove(p);
	
}
public float getTotalPrice(){
	float sum = 0;
	for(int i=0; i<c.size(); i++){
		
		sum +=  c.get(i).getPrice();
	}
	return sum;
}
public String getReceipt(Paraggelia a){
	String s="";
	for(int i=0; i< c.size(); i++){
		
	s += "Food: "+c.get(i).getName() + " " + "Barcode: "+c.get(i).getBarcode() + " " + "Price: "+c.get(i).getPrice() + " " + "Table: "+a.getTablenumber()+"\n";
		
	}
	return s;
}




}



