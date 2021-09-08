#include <stdio.h>
#include <string.h>

char A[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnoprqstuvwxyz"; //62 + '/0' = 37 2 3



void caesar_encrypt(char *plaintext, int N){
	int i,x,y,rc,tempc,cnt,tmpN;
	char temp1,temp2;
	
	
	for( i = 0; plaintext[i] != '\0'; ++i){
		tmpN=N;
		temp1 = plaintext[i];
		

		if(plaintext[i] >= 'a' && plaintext[i] <= 'z'){
			plaintext[i] = plaintext[i] + N;
			

		 	if(temp1 + N > 'z'){

				for(x = 0; A[x] != '\0'; x++){
					
				if(A[x] == temp1){
					while(tmpN){
							tmpN--;
							temp1=A[x];
							if(A[x] == 'z'){
								x=0;
							}
							A[x++];
					}
					plaintext[i]=temp1;
				
				}
			
			}
			}
			}	
				
		
			temp2 = plaintext[i];

		if(plaintext[i] >= 'A' && plaintext[i] <= 'Z'){
			plaintext[i] = plaintext[i] + N;
			
		 	if(temp2 + N > 'Z'){

				for(y = 0; A[y] != '\0'; y++){
				
				if(A[y] == temp2){
					A[y++];
					while(tmpN){
							tmpN--;
							temp2=A[y];
							if(A[y] == 'z'){
								y=0;
							}
							A[y++];
					}
					plaintext[i] = temp2;
				}
				}
				
				
		}
		
	}

		if(plaintext[i] >= '0' && plaintext[i] <= '9'){
				plaintext[i] = plaintext[i] + N;

				if(temp1 + N > 9){
					for(x = 0; A[x] != '\0'; x++){
					
					if(A[x] == temp1){
						A[x++];
						while(tmpN){
							temp1=A[x];
							tmpN--;
							if(A[x] == 'z'){
								x=0;
							}
							A[++x];
					}
					plaintext[i]=temp1;
				
				}
			}
		}
			
	}

}



					 
	}


//char A[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
void caesar_decrypt(char *ciphertext, int N){
	
	int i,x,y,rc,tempc,cnt,tmpN;
	char temp1;
	for( i = 0; ciphertext[i] != '\0'; ++i){
		tmpN = N;
		temp1 = ciphertext[i];
		

		if(ciphertext[i] >= 'a' && ciphertext[i] <= 'z'){
			ciphertext[i] = ciphertext[i] - N;
			

		 	if(temp1 - N < 'a'){

				for(x = 0; A[x] != '\0'; x++){
					
				if(A[x] == temp1){
					
					while(tmpN){
							tmpN--;
							A[x--];
							temp1=A[x];
							if(A[x] == '0'){
								x=62;
							}
							
							
					}
							ciphertext[i]=temp1;
							
				
				}
			
			}
			}
			}
		
	
		

			
		else if(ciphertext[i] >= 'A' && ciphertext[i] <= 'Z'){
			ciphertext[i] = ciphertext[i] - N;
			
		 	if(temp1 - N < 'A'){

				for(y = 0; A[y] != '\0'; y++){
				
				if(A[y] == temp1){
					
					while(tmpN){
							tmpN--;
							A[y--];
							temp1=A[y];
							if(A[y] == '0'){
								y=62;
							}
							
					}
					ciphertext[i] = temp1;
				}
				}
				
				
		}
		
	}


//char A[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

		else if(ciphertext[i] >= '0' && ciphertext[i] <= '9'){
				ciphertext[i] = ciphertext[i] - N;

				if(temp1 - N < '0' ){
					for(x = 0; A[x] != '\0'; x++){
					
					if(A[x] == temp1){

						while(tmpN+1){
							tmpN--;
							A[x--];
							temp1=A[x];
							if(A[x] == 0){
								x=62;
							}
							
							
					}
					ciphertext[i]=temp1;
				
				}
			}
		}
			
	}

}

		}