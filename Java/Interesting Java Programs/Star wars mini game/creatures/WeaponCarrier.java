package csd;

public abstract class WeaponCarrier {
Weapon weapon;

Weapon getWeapon(){
	return weapon;
}
Boolean hasWeapon(){
	if(getWeapon() != null){
		return true;
	}else
		return false;
}

void setWeapon(Weapon weapon){
	this.weapon = weapon;
}
}
