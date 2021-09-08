package csd;

import java.util.Random;

public abstract class Droid {
	String name;
	Humanoid master;
	String validNameChars = 
	        new String("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	Droid(){
		Random r = new Random(); 
	int n = validNameChars.length(); 
	String result = new String(); 
	for (int i=0; i<4; i++){
	    result = result + validNameChars.charAt(r.nextInt(n));
	}
	name = result;
	return;
	}
	
	Droid(Humanoid master){
		Droid d = new Droid(){};
		this.master = d.master;
	}
	void setMaster(Object master){
		if(master instanceof Jedi){
			this.master=(Jedi)master;
		}else if(master instanceof Sith){
			this.master = (Sith)master;
		}
	}
	Humanoid getMaster(){
		return master;
	}
	String getName(){
		return name;
	}
	boolean isFree(){
		if(getMaster()==null||getMaster().getCondition()==0){
			return true;
		}else 
			return false;
	}
	public String toString(){
		return "Droid: "+name +" "+"Master: "+master.getCallSign();
	}
}