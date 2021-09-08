package csd;



public class BattleDroid extends Droid {
int condition;

BattleDroid(){
	condition = 10;
}
BattleDroid(Humanoid master){
	super(master);
}
int getCondition(){
	return condition;
}
void setCondition(int condition){
	this.condition = condition;
}
String getCallSign(){
	return name;
}
void attack(Object adversary){
	if(adversary instanceof Jedi){
		Jedi p = (Jedi)adversary;
		System.out.println("robot atack "+p.getCallSign());
		p.health--;
		System.out.println(p.getCallSign()+" condition is "+p.getCondition());
		System.out.println(name+" was just protecting its master "+master.getCallSign());
	}else 
		if(adversary instanceof Sith){
			Sith p = (Sith)adversary;
			p.health--;
			System.out.println(p.getCallSign()+" condition is "+p.getCondition());
			System.out.println(name+" was just protecting its master "+master.getCallSign());
		}
}
boolean isDeafeated(){
	if(getCondition()==0){
		return true;		
	}else 
		return false;
}
void protectMasterFrom(Object adversary){
	if(adversary instanceof Jedi){
		Jedi p = (Jedi)adversary;
		if(p.getCondition()>0){
			System.out.println(name+" atacked "+p.getCallSign());
			 attack(p);
		}
	}else 
		if(adversary instanceof Sith){
			Sith p = (Sith)adversary;
			if(p.getCondition()>0){
				System.out.println(name+" atacked "+p.getCallSign());
				 attack(p);
			}
}
}
}
