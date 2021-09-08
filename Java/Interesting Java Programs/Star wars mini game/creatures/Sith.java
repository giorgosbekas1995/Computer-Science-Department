package csd;

public class Sith extends Humanoid implements Combatant {

	Sith(String lastName){
		super(lastName);
	}

	public String toString() {
		return firstName + " " + lastName + " " +weapon;
	}

	public void attack(Object adversary) {
		Jedi p = (Jedi)adversary;
		System.out.println(firstName+" "+lastName+" attacked"+" "+p.firstName+" "+p.lastName);
		if(hasWeapon()){
			p.health = p.health -  weapon.power;
		}else p.health = p.health - 1;
		System.out.println(p.getCallSign()+" condition is "+p.getCondition());
	}
	


	public boolean isDefeated() {
		if(getCondition()<=0){
			return true;
		}else
		return false;
	}
	public void setCondition(int condition){
		if(condition>=1&&condition<=10){
			health = condition;
			}else{
				System.out.println("Invalid condition try again");
			}
	}
	public int getCondition(){
		if(health<0){health = 0;}
		return health;
		
	}
	public String getCallSign(){
		return firstName + " " + lastName;
		
	}
}
