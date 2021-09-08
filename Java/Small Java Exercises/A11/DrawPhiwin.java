import java.util.Scanner;
import javax.swing.JOptionPane;

public class DrawPhiwin{
     public static void main(String [] args){
     int L;
     String s="";                                                                       //kanei thn idia doulia me thn DrawPhi apla ta space kai ta asterakia ta 
while(true){                                                                            //apothikeuoume se string gia na tipwsoume to string 
   	 L = Integer.parseInt(JOptionPane.showInputDialog( "Give me a number ", 4));
	if(L<4||L>30){
	    System.out.println("Out of range bye");
	     break;
	}

     	for(int i=1;i<=L/2;i++){
		
			for(int j=1;j<=L-i ;j++){
			s+="  ";
			}
     		
		for(int k=1;k<=2*i-1 ;k++){
			if(k==1||k==(2*i)/2||k==2*i-1){
			s+=" *";
				}else s+="  ";
			
			}
			s+="\n\n";
	
		}

if(L%2==1){
	for(int i=L/2+1;i>=1;i--){
		
			
			for(int j=1;j<=L-i ;j++){
			s+="  ";
			}
     		
		for(int k=1;k<=2*i-1 ;k++){
			
			if(k==1||k==(2*i)/2||k==2*i-1){
				s+=" *";
				}else 
				s+="  ";
			}
			s+="\n\n";
	}
JOptionPane.showMessageDialog(null, s);
}
if(L%2==0){
	for(int i=L/2;i>=1;i--){
		
			for(int j=1;j<=L-i ;j++){
			s+="  ";
			}
     		
		for(int k=1;k<=2*i-1 ;k++){
			if(k==1||k==(2*i)/2||k==2*i-1){
			s+=" *";
				}else 
				s+="  ";
			}
			s+="\n\n";
				}
	JOptionPane.showMessageDialog(null, s);
			}
             
		}

	}

}	
