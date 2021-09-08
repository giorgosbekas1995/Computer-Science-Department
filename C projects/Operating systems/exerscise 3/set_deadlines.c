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
sys_set_deadlines(int pid, int soft, int hard, int expected)
{	
	struct task_struct *i;
	int flag = 0;
	
	printk("Giorgos Bekas Called system call set_deadlines_sys with arguments: %d %d %d %d\n", pid, soft, hard, expected);
	
	if (pid < -1 || hard <= soft || expected < 0 )
		return EINVAL;
	
	if( pid == -1 )
		pid = task_pid_nr(current);
	
	for_each_process(i)
	{
		if( task_pid_nr(i) == pid )
		{
			flag = 1;
			i->soft_deadline = soft;
			i->hard_deadline = hard;
			i->expected_computation = expected;
			printk("BEKAS soft = %d hard = %d expected = %d \n", i->soft_deadline, i->hard_deadline, i->expected_computation);
		}
	}
	
	if (flag == 0)
	{
		printk("Process with pid %d not found\n", pid);
		return EINVAL;
	}
	
	return 0;
}
