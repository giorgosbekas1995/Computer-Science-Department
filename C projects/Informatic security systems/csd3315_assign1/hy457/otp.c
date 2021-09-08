#include "otp.h"

char * otp_encrypt(char *plaintext, char *key);
char * otp_decrypt(char *ciphertext, char *key);

int main(void){

char *encrypted;
char *decrypted;
int randomData = open("/dev/urandom", O_RDONLY);
char key[50];
char message[50];

scanf("%s", message);
read(randomData, key, sizeof(key));
printf("Encrypted message: ");
encrypted = otp_encrypt(message,key);
printf("Decrypted message: ");
decrypted = otp_decrypt(encrypted,key);


  


}


