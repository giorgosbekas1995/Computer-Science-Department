#include "caesars.h"


void caesar_encrypt(char *plaintext, int N);
void caesar_decrypt(char *ciphertext, int N);

int main(){
	char message[50];
	int N,N2;
	
	scanf("%s", message);
	scanf("%d", &N);
	N2 = N;
	caesar_encrypt(message,N);
	printf("Encrypted message: %s\n",message);
	caesar_decrypt(message,N2);
	printf("Decrypted message: %s\n",message);
	
}


	
