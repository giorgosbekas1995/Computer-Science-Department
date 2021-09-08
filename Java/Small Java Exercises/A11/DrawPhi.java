import java.util.Scanner;


public class DrawPhi{
     public static void main(String [] args){
     int L;
    
while(true){
	Scanner in = new Scanner(System.in);	                       //otan dwsoume arithmo <4 kai >30 to programa tha stamatisei na trexi
        L=in.nextInt();

	if(L<4||L>30){
	     System.out.println("Out of range bye");
	     break;
	}

     	for(int i=1;i<=L/2;i++){ //se auth th for ftiaxnoume to miso ö 
		
			for(int j=1;j<=L-i ;j++){   //tipwnei to kena pou xriazomaste. Gia paradeigma an L=10
			System.out.print("  ");     // thn prwth fora tipwnei 9 kena meta 8 ktlp. tha to kanei omws L/2 fores
			}			    //giati h prwth for ekteleitai L/2 fores
     		
		for(int k=1;k<=2*i-1 ;k++){
			if(k==1||k==(2*i)/2||k==2*i-1){       //edw tiponoume ta asterakia stis theseis pou theloume wste na sximatistei to ö
			System.out.print(" *");		      //kai stis ipolipes ektipwnoume keno gia na min fenete tipota
				}else System.out.print("  ");
			
			}
			System.out.print("\n");
		}
if(L%2==1){             
	for(int i=L/2+1;i>=1;i--){          //edw kanoume to deutero miso komati tou ö me antistixo tropo alla mono gia peritous arithmous
		
			
			for(int j=1;j<=L-i ;j++){
			System.out.print("  ");
			}
     		
		for(int k=1;k<=2*i-1 ;k++){
			
			if(k==1||k==(2*i)/2||k==2*i-1){
			System.out.print(" *");
				}else 
				System.out.print("  ");
			
			}
			System.out.print("\n");
	}
}
if(L%2==0){
	for(int i=L/2;i>=1;i--){      //edw kanoume to deutero miso komati tou ö me antistixo tropo alla mono gia artious arithmous
		
			for(int j=1;j<=L-i ;j++){
			System.out.print("  ");
			}
     		
		for(int k=1;k<=2*i-1 ;k++){
			if(k==1||k==(2*i)/2||k==2*i-1){
			System.out.print(" *");
				}else 
				System.out.print("  ");
			
			}
			System.out.print("\n");
				}
			}
		}
	}

}	
