#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

pid_t fork(){

printf("this is my fork it always returns 0 ");

return 1;
}
