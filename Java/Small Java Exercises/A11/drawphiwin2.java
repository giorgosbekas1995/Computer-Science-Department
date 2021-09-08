import java.util.Scanner;
import javax.swing.JOptionPane;

public class drawphiwin2{
     public static void main(String [] args){                      //kanei idia doulia me thn DrawPhiwin apla anti gia asterakia ektipwnei arithmous
     int L;
     String s="";
while(true){
   	 L = Integer.parseInt(JOptionPane.showInputDialog(
                    "Give me a number ", 4));

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
			s+=" "+i;
				}else s+="  ";
			
			}
			s+="\n\n";
	
		}

if(L%2==1){ int a=L/2+1;
	for(int i=L/2+1;i>=1;i--){
		
			
			for(int j=1;j<=L-i ;j++){
			s+="  ";
			}
     		
		for(int k=1;k<=2*i-1 ;k++){
			
			if(k==1||k==(2*i)/2||k==2*i-1){
				s+=" "+a;
				}else 
				s+="  ";
			}
			s+="\n\n";
			a++;
	}
JOptionPane.showMessageDialog(null, s);
}
if(L%2==0){ int b=L/2+1;
	for(int i=L/2;i>=1;i--){
		
			for(int j=1;j<=L-i ;j++){
			s+="  ";
			}
     		
		for(int k=1;k<=2*i-1 ;k++){
			if(k==1||k==(2*i)/2||k==2*i-1){
			s+=" "+b;
				}else 
				s+="  ";
			}
			s+="\n\n";
			b++;
				}
	JOptionPane.showMessageDialog(null, s);
			}
             
		}

	}

}	
