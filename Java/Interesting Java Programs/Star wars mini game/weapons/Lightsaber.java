package csd;

enum COLOR{
	RED,BLUE
}

public class Lightsaber extends Weapon {
COLOR color;

Lightsaber(){
	super();
}

COLOR getColor(){
	return color;
}
public String toString(){
	return this.color + " " + power;
}
void setHolder(Object holder){
	this.holder = (WeaponCarrier) holder;
if(holder instanceof Sith){
	color=COLOR.RED;
}else if(holder instanceof Jedi){
	color=COLOR.BLUE;
}
}
}
