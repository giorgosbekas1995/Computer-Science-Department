
package csd;

public class koumparas {
            float sum=0;
            int capasity;
           public koumparas(int c ){
                  						//constructor
                 capasity = c;
            }
    
            public koumparas() {} 

			int getCapasity(){
                return capasity;
            }
           
            boolean Brake(){
                if(capasity > 0){   //elegxoume an einai gematos o koumparas gia na doume an ton spasoume
                	return false;
                }else{
           System.out.println("Spase ton koumpara einai gematos!!");
                  return true;
                }
        
                }
            
            
            float add(float money ){ //oso o koumparas exei xwro vazoume xrimata kai ipologizoume posa leuta exoume mexri twra
               
                	if(!Brake()){
                	if(capasity==1 && money > 2){
                		System.out.print("den xwraei to poso "+ money +" vazw " +capasity+" euro\n");
                		sum += capasity;
                		capasity--;
                	}else
                	if(money<=2){
                        sum+=money;
                        capasity--;
                	}else
                        if(money>2){
                        sum += money;
                        capasity = capasity-2;
                        }
               
                	}
                   return sum;
            }
}

                   
       
  
