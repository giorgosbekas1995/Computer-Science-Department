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
sys_set_demand(int pid, int demand)
{
	static int total_demand = 0;
	
	struct task_struct *i;
	int flag = 0;
	
	printk("Giorgos Bekas Called system call set_demand_sys with arguments: %d %d\n", pid, demand);
	
	if (pid < -1 || demand < 0 || ((total_demand + demand) > 100))
		return EINVAL;
	
	if( pid == -1 )
		pid = task_pid_nr(current);
	
	for_each_process(i)
	{
		if( task_pid_nr(i) == pid )
		{
			flag = 1;
			total_demand  += demand;
			i->demand = demand;
			printk("BEKAS i->demand = %d\n", i->demand);
		}
	}
	
	if (flag == 0)
	{
		printk("Process with pid %d not found\n", pid);
		return EINVAL;
	}
	
	return 0;
}
