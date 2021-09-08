#include <stdio.h>
#include <string.h>

void spartan_encrypt(char *plaintext, int circ, int len);




int main(){

char *encrypted;
char *decrypted;
int  circ,len;
char message[50];



scanf("%d", &circ);
scanf("%d", &len);
scanf("%s", message);


spartan_encrypt(message,circ,len);


printf("\n");

}


void spartan_encrypt(char *plaintext, int circ, int len){
char msgencrypt[circ][len];
char encryptedmsg[50];
int cnt = 0,k=0;

for(int i=0; i <= circ; i++){ 
	for(int x=0; x < len; x++){
		
		if(plaintext[cnt] == '\0'){

		 msgencrypt[i][x] = '#';
		}

		msgencrypt[i][x] = plaintext[cnt];
			cnt++;

	}
}

printf("Encrypted message : ");
for(int i=0; i <= circ; i++){  
	for(int x=0; x < len; x++){
		encryptedmsg[k] = msgencrypt[x][i];
		printf("%c",encryptedmsg[k]);
		k++;
	}
	
}


}

