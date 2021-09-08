import java.util.Random;

public class CyclicCalls{
static int z;
public static void main(String[] args){
m1(10);

}




public static void m1(int x){
double random = new Random().nextDouble();
System.out.println("m1 called with argument "+x);      //sinartisi m1:ektipwnei oti kalestike me 10 polaplasiazei ton arithmo 10 me enan tixeo arithmo 0.1-1 ton strogkilopoei
random=random*x;                                       //kai kalei thn m2 me auton ton arithmo
z = (int) random;
m2(z);
	}


public static void m2(int y){
if(y==9){                                 //sinartish m2: an o arithmos pou kalestike h sinartisi einai 9 ektipwnei bingo kai stamataei
	System.out.print("Bingo!!");      //to programa aliws ektipwnei kai kalei pisw thn m1 me orisma 10
	System.exit(0);
}
System.out.println("m2 called with argument "+y);
m1(10);
	}


}