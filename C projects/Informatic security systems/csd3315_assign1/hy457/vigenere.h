#include <stdio.h>
#include <string.h>

char * vigenere_encrypt(char *plaintext, char *key){
	char encrypted[50];
	for(int i = 0; plaintext[i] != '\0'; i++){
		encrypted[i] = ((plaintext[i] + key[i]) % 26) + 65;
	}
	return encrypted;
}

char * vigenere_decrypt(char *plaintext, char *key){
	char decrypted[50];
	for(int i = 0; plaintext[i] != '\0'; i++){
		decrypted[i] = (((plaintext[i] - key[i]) + 26) % 26) + 65;
	}
	return decrypted;
}