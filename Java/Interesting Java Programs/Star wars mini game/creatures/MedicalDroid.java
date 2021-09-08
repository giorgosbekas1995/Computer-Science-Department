package csd;

import java.util.Random;

public class MedicalDroid extends Droid{
int MedicalSkills;

MedicalDroid(){
	Random obj = new Random();
	MedicalSkills = obj.nextInt(3) + 1;
}
MedicalDroid(Humanoid master){
	super(master);
}
int getMedicalSkills(){
	return MedicalSkills;
}
String getName(){
	return name;
}
void healMaster(){
	master.health += getMedicalSkills();
	System.out.println(name+" healed "+getMedicalSkills()+" units of its master "+master.getCallSign());
	System.out.println(master.getCallSign()+" condition: "+master.health);
}
}
