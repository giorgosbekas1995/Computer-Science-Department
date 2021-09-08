package csd;

import java.util.Random;

public class battle {
        
    public static void main(String[] args) {
    	Lightsaber q = new Lightsaber();
    	Lightsaber o = new Lightsaber();
        Jedi obiwan = new Jedi("Obiwan", "Kenobi");
        q.setHolder(obiwan);
        obiwan.setWeapon(q);
        System.out.println(obiwan);
        
        Sith vader = new Sith("Vader");
        o.setHolder(vader);
        vader.setWeapon(o);       
        System.out.println(vader);
        
        MedicalDroid docDroid = new MedicalDroid();
        docDroid.setMaster(vader);
        System.out.println(docDroid);
        
        BattleDroid battleDroid = new BattleDroid();
        battleDroid.setMaster(obiwan);
        System.out.println(battleDroid);
        
        //battle between jedi and sith
        try {
            while (!obiwan.isDefeated() && !vader.isDefeated()) {
                //random turn
                if (new Random().nextBoolean()) {
                    obiwan.attack(vader);
                    if (!vader.isDefeated()) {
                        vader.attack(obiwan);
                    } 
                } else {
                    vader.attack(obiwan);
                    if (!obiwan.isDefeated()) {
                        obiwan.attack(vader);                    
                    } 
                }                
                if (!docDroid.isFree()) {
                    docDroid.healMaster();
                }
                if (!battleDroid.isFree() && !vader.isDefeated()) {
                    battleDroid.protectMasterFrom(vader);
                }
                System.out.println();
            }
        }catch (Exception e) {
            System.err.println(e);
        } finally {
            System.out.print(obiwan.isDefeated()? vader.getCallSign() : obiwan.getCallSign());
            System.out.println(" won!");
        }
    }
    
}