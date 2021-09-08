package csd;

import java.util.Random;

public abstract class Weapon {
int power;
WeaponCarrier holder;


Weapon(){
	Random obj = new Random();
	power = obj.nextInt(5) + 1;
}
 int getPower(){
	return power;
}
void setHolder(Object holder){
        this.holder = (WeaponCarrier) holder;
}

WeaponCarrier getHolder(){
	return holder;	
}
public abstract String toString();
}
