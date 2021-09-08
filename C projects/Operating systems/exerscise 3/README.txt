Giorgos Bekas
Άσκηση 3 hy-345

set_deadlines(int pid, int soft, int hard, int expected);
get_deadlines(int pid, struct d_params *d_arguments);

1.
#define __NR_set_deadlines 341 /* bekas */
#define __NR_get_deadlines 342 /* bekas */

2.
	.long sys_set_deadlines /* 341  bekas */
	.long sys_get_deadlines /* 342  bekas */
	
3.
#ifndef sys_set_demand
asmlinkage long sys_set_deadlines(int pid, int soft, int hard, int expected);
#endif

#ifndef sys_get_demand
asmlinkage long sys_get_deadlines(int pid, struct d_params *d_arguments);
#endif


4.
obj-y += get_deadlines.o
obj-y += set_deadlines.o

5. .config
CONFIG_LOCALVERSION="-hy345 bekas 2"
