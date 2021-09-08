package csd;

public abstract class Humanoid extends WeaponCarrier {
String firstName;
String lastName;
int health;

Humanoid(String firstName,String lastName, int health){
	this.firstName = firstName;
	this.lastName = lastName;
	this.health = health;
}
Humanoid(String firstName,String lastName){
	this.firstName = firstName;
	this.lastName = lastName;
	health	= 10;
}
Humanoid(String lastName){
	firstName = "Darth";
	this.lastName = lastName;
	health	= 10;
}

void setHealth(int health){
	this.health = health;
}

int getHealth(){
	return health;
}
void setCondition(int cond){
	if(cond>=1&&cond<=10){
	setHealth(cond);
	}else 
		System.out.println("Invalid condition try again");
}
int getCondition(){
	return getHealth();
}
boolean isDeated(){
	if(getCondition()==0){
		return true;
	}else 
		
		return false;
}
String getCallSign(){
	return firstName + " " + lastName;
}
public abstract String toString();
}
