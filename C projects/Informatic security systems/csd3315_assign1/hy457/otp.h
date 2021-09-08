#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char *otp_encrypt(char *plaintext, char *key){
	int i;
	char encrypted[50];
	for (i=0; plaintext[i] != '\0'; i++){

	encrypted[i] = plaintext[i]^key[i];
	printf(" %X \t",encrypted[i]);
	}
	printf("\n");
	return encrypted;
}


char *otp_decrypt(char *ciphertext, char *key){
	int i;
	char decrypted[50];
	for ( i=0; ciphertext[i] != '\0'; i++){

	decrypted[i] = ciphertext[i]^key[i];
	printf(" %X=%c \t",decrypted[i],decrypted[i]);
	}
	printf("\n");
	return decrypted;
}
