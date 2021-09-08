package csd;

import java.util.Random;

enum Rank {
YOUNGLING,PADAWAN,KNIGHT,MASTER,GRAND_MASTER
}

public  class Jedi  extends Humanoid implements Combatant {
Rank rank;
int force_level;
Random obj = new Random();

Jedi(String firstName, String lastName) {
		super(firstName, lastName);	
force_level = obj.nextInt(100) + 1;
if(force_level<10){
rank = Rank.YOUNGLING;
}
if(force_level>=10&&force_level<30){
rank = Rank.PADAWAN;
}
if(force_level>=30&&force_level<70){
rank = Rank.KNIGHT;
}
if(force_level>=70&&force_level<90){
rank = Rank.MASTER;
}
if(force_level>=90&&force_level<=100){
	rank = Rank.GRAND_MASTER;
}

}

int getForceLevel(){
	return force_level;
}
Rank getRank(){
	return rank;
}


public String toString() {
	
	return firstName+" "+lastName+" "+rank+" "+weapon;
}

public int getCondition(){
	if(health<0){health = 0;}
	return health;
}
public void setCondition(int condition){
	if(condition>=1&&condition<=10){
	health = condition;
	}else{
		System.out.println("Invalid condition try again");
	}
}

public String getCallSign(){
	return firstName+" "+lastName;
}


public void attack(Object adversary) {
	
	Sith p = (Sith)adversary;
	if(getCondition()>0){
		int rank_power = 0;
		System.out.println(firstName+" "+lastName+" attacked"+" "+p.firstName+" "+p.lastName);
		if(rank==Rank.YOUNGLING){
			rank_power=0;
		}else
		if(rank==Rank.PADAWAN){
			rank_power=1;
		}else
		if(rank==Rank.KNIGHT){
			rank_power=2;
		}else
		if(rank==Rank.MASTER){
			rank_power=3;
		}else
		if(rank==Rank.GRAND_MASTER){
			rank_power=4;
		}
	
		if(hasWeapon()){
			p.health = p.health - (rank_power + weapon.power);
		}else p.health = p.health - (rank_power+1);
	}
	System.out.println(p.getCallSign()+" condition is "+p.getCondition());
}

public boolean isDefeated() {
	if(getCondition()<=0){
		return true;
	}else
	return false;
}


}
