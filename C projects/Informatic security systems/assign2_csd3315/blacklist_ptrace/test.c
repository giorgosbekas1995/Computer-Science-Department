#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/reg.h>


int main(int argc, char *argv){


printf("Hello\n");
FILE *fp;

fp = fopen("/tmp/test.txt", "w+");
fprintf(fp, "This is testing for fprintf...\n");
fputs("This is testing for fputs...\n", fp);
fclose(fp);

fp = fopen("/tmp/test.txt", "r");

printf("A file crearted\n");

execl("/bin/w", "w", NULL);

}
