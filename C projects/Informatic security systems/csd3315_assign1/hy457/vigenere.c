#include "vigenere.h"

char * vigenere_encrypt(char *plaintext, char *key);
char * vigenere_decrypt(char *ciphertext, char *key);

int main(){

char *encrypted;
char *decrypted;
char key[50];
char msgkey[50];
char message[50];


scanf("%s", message);
scanf("%s", key);
printf("\n");
for(int i = 0, x = 0; i < message[i] != '\0'; i++, x++){
	if( x == strlen(key)){
		x = 0;
	}
	msgkey[i] = key[x];
}

encrypted = vigenere_encrypt(message,msgkey);
printf("Encrypted message: %s\n",encrypted);
decrypted = vigenere_decrypt(encrypted,msgkey);
printf("Decrypted message: %s\n",decrypted);


}


