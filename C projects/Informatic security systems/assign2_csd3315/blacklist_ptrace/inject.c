#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/reg.h>

//#define  __NR_read 0 
//#define  __NR_write 1 
//#define  __NR_open 2
//#define  __NR_close 3
//#define  __NR_stat 4 

int main(int argc, char *argv)
{
    int count_all=0;
    int count_not=0;
    pid_t child;
    int status, syscall_nr;

    child = fork();
    if (child == 0) {
        /* In child. */
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execve("test", NULL, NULL);
        // not reached
    }

    /* In parent. */
    while (1) {
        wait(&status);

        /* Abort loop if child has exited. */
        if (WIFEXITED(status) || WIFSIGNALED(status))
            break;

        /* Obtain syscall number from the child's process context. */
        syscall_nr = ptrace(PTRACE_PEEKUSER, child, 4 * ORIG_EAX, NULL);
        printf("Child wants to execute system call %d: ", syscall_nr);

        if ((syscall_nr != 0) && (syscall_nr != 1) && (syscall_nr != 2) && (syscall_nr != 3) && (syscall_nr != 4)) {
            /* Allow system call. */
            printf("allowed.\n");
            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
	    count_all++;
        } else {
            /* Terminate child. */
            printf("not allowed. Terminating child.\n");
            ptrace(PTRACE_KILL, child, NULL, NULL);
	    count_not++;
        }
    }

    printf("syscalls allowed : %d\n",count_all);
    printf("syscalls not_allowed : %d",count_not);

    exit(EXIT_SUCCESS);
}
