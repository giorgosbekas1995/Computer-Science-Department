#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h>
#include <stdio.h>

int main(int argc, char **argv)
{   
    pid_t child;
    long orig_eax;
    int status;

    child = fork();
    if(child == 0) 
    {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	execve("test", NULL , NULL);
    }
    else 
    {
        /* Both wait and waitpid works */
        //wait(NULL);
        waitpid(child, &status, 0);
       
        
        
        fprintf(stdout, "fork didnt invoke\n");

        ptrace(PTRACE_KILL, child, NULL, NULL);
        
    }

    return 0;
}
