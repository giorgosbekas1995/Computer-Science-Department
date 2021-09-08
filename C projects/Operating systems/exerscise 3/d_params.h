/* Bekas Code */
#ifndef _LINUX_D_PARAMS_H
#define _LINUX_D_PARAMS_H 1

#include <linux/types.h>

struct d_params 
{
	int soft_deadline;
	int hard_deadline;
	int expected_computation;
};

#endif
