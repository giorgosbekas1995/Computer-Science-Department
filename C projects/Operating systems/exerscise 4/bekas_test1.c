#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define set_demand 341
#define get_demand 342

struct d_params{int demand;};

int main(int argc, char ** argv)
{

	long ret;
	struct d_params *d_arguments;
	int i = 0;
	int j = 0;
	int sum = 0;
	
	d_arguments = malloc(sizeof(struct d_params));
	
	printf("Test set_demand system call\n");
	ret = syscall(set_demand, -1, 20);
	
	if ( errno == EINVAL || ret != 0 )
		printf("system call returned error\n");
	else
		printf("system call setted demand\n");
	
	printf("Test get_demand system call\n");
	
	ret = syscall(get_demand, -1, d_arguments);
	

	for (i = 0; i < 1000000; i++)
	{
		for (j= 0; j < 1000000; j++)
			sum = i + j + sum;
	}
	return 0;
}

