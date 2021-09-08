#ifndef __TCODEH__
#define __TCODEH__

enum vmopcode {
	assign_v, 
	add_v, 
	sub_v,
	mul_v, 
	div_v, 
	mod_v,
	uminus_v, 
	and_v, 
	or_v, 
	not_v, 
	jeq_v, 
	jne_v, 
	jle_v, 
	jge_v, 
	jlt_v,
	jgt_v, 
	call_v, 
	pusharg_v, 
	funcenter_v, 
	funcexit_v, 
	newtable_v,
	tablegetelem_v, 
	tablesetelem_v, 
	jump_v,
	nop_v
};

typedef enum vmopcode vmopcode;

enum vmarg_t {
	label_a = 0,
	global_a, 
	formal_a,
	local_a,
	number_a,
	string_a,
	bool_a,
	nil_a,
	userfunc_a,
	libfunc_a,
	retval_a 
};
typedef enum vmarg_t vmarg_t;

struct vmarg { 
	vmarg_t type; 
	unsigned val; 
};
typedef struct vmarg vmarg;

struct instruction {
	vmopcode opcode; 
	vmarg *result, *arg1, *arg2; 
	unsigned srcLine;
};
typedef struct instruction instruction;

struct userFunc{
	unsigned address;
	unsigned localSize;
	char *id;
};
typedef struct userFunc userFunc;

double *numCosts;
unsigned totalNumCosts;

char **stringConsts;
unsigned totalStringConsts;

char **namedLibFuncs;
unsigned totalNamedLibFuncs;

userFunc* userFuncs;
unsigned totalUserFuncs;

unsigned consts_newstring(char* s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(char* s);
unsigned userfuncs_newfunc(symbol *f);


struct incomplete_jump {
	unsigned instNo;
	unsigned iaddress;
	struct incomplete_jump* next;
};
typedef struct incomplete_jump incomplete_jump;


#endif
