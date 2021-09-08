package csd;

import java.util.Scanner;


public class KoymparasClient {
    public static void main(String[] args) {
        koumparas o = new koumparas();
        o.capasity = 10;
        Scanner  scan = new Scanner(System.in);
        
        while(!o.Brake()){
            float money = scan.nextFloat();
            o.add(money);
        }
          
        o.add(10); //prospatheia na valoume leuta afou einai gematos o koumparas
        System.out.println("Meta to spasimo tou koumpara exoume "+o.sum+" euro");
        
    }
    
}
