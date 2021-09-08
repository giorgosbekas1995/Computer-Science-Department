package askisi31;

import java.util.Random;

import org.jfugue.Player;

public class ArrayManager {
	public static void main(String[] args){
		int[] p1= new int[20];
		int[] p2= new int[20];
	     fillRandom(50,120,p1);
	     fillFrom(p2,p1);
	     playMusic(p2);
	     
	}
	
  

public static void fillRandom(int min, int max, int[] ar){ // sinartisi pou gemizi ton pinaka me tixeous arithmous gia
		                                                   //kapio sigkekrimeno diastima pou epilegoume emeis
		for(int i=0; i<ar.length; i++ ){
			int random = new Random().nextInt(max - min) + min;
			ar[i]=random;
		}
	}
 
public static void fillFrom(int[] ar, int[] fromArr){//enas pinakas antigrafei ta stoixeia tou allou mono an oi pinakes
	if(ar.length!=fromArr.length){                   //exoun idio megethos
		System.out.println("arrays dont have same size");
			}else
	for(int i=0; i<ar.length; i++){
		ar[i]=fromArr[i];
		}
	}
public static void playMusic(int[] ar){//sinartisi pou mousikopoiei kathe stoixeio tou pinaka
	Player p = new Player();
	for(int i=0; i<ar.length; i++){
		p.play("["+ar[i]+"]");
	}
	
}

}



