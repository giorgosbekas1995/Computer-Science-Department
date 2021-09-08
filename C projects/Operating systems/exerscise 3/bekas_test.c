#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define set_deadlines 341
#define get_deadlines 342

struct d_params{
	int soft_deadline;
	int hard_deadline;
	int expected_computation;
};

int main(int argc, char ** argv)
{
	long ret;
	struct d_params *d_arguments;
	int pid;
	int child;
	
	d_arguments = malloc(sizeof(struct d_params));
	
	printf("Test set_deadlines system call\n");
	ret = syscall(set_deadlines, -1, 20, 30, 10);
	
	if ( errno == EINVAL || ret != 0 )
		printf("system call returned error\n");
	else
		printf("system call set deadlines\n");
	
	printf("Test get_dealines system call\n");
	
	ret = syscall(get_deadlines, -1, d_arguments);
	
	if ( ret != 0 )
		printf("system call returned error\n");
	else
		printf("system get_deadlines executed without problems\n soft = %d hard = %d computation = %d \n", d_arguments->soft_deadline, d_arguments->hard_deadline, d_arguments->expected_computation);
	
	/* TEST twn systemcalls me fork */
	pid = getpid();
	child = fork();
	if ( child < 0)
		return -1;
	else if (child > 0);
	{
		child = getpid();
		ret = syscall(get_deadlines, child, d_arguments);
		if ( ret != 0 )
			printf("system call returned error\n");
		else
			printf("system get_deadlines executed without problems\n soft = %d hard = %d computation = %d \n", d_arguments->soft_deadline, d_arguments->hard_deadline, d_arguments->expected_computation);
			return 0;
	}
	else
	{
		child = getpid();
		ret = syscall(get_deadlines, child, d_arguments);
		if ( ret != 0 )
			printf("system call returned error\n");
		else
			printf("system get_deadlines executed without problems\n soft = %d hard = %d computation = %d \n", d_arguments->soft_deadline, d_arguments->hard_deadline, d_arguments->expected_computation);
			return 0;
	}
	return 0;
}

