/* Bekas Code */
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <asm-generic/errno-base.h>
#include <linux/types.h>
#include <linux/d_params.h>

asmlinkage long
sys_get_demand(int pid, struct d_params *d_arguments)
{
	struct task_struct *i;
	int flag = 0;
	
	printk("Giorgos Bekas Called system call get_demand_sys with arguments: %d and point d_arguments\n", pid);
	
	if (pid < -1 || d_arguments == NULL)
		return EINVAL;
	
	if( pid == -1 )
		pid = task_pid_nr(current);
	
	for_each_process(i)
	{
		if( task_pid_nr(i) == pid )
		{
			flag = 1;
			d_arguments->demand = 50;
			d_arguments->demand = i->demand;
		}
	}
	
	if (flag == 0)
	{
		printk("Process with pid %d not found\n", pid);
		return EINVAL;
	}
	 
	return 0;
}
