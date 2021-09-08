
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>



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

struct userFunc* userFuncs;
unsigned totalUserFuncs;

/*
unsigned consts_newstring(char* s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(char* s);
unsigned userfuncs_newfunc(userFunc **sym);
*/

unsigned char           executionFinished = 0;
unsigned                pc = 0;
unsigned                currLine = 0;

//to code einai ta instructions apo tin 4h fasi
unsigned                codeSize = 0;
instruction*   			code = (instruction*)  0;

#define AVM_EDITING_PC 	codeSize


#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

void	execute_assign(instruction* instr);
void	execute_add(instruction* instr);
void	execute_sub(instruction* instr);
void	execute_mul(instruction* instr);
void	execute_div(instruction* instr);
void	execute_mod(instruction* instr);
void	execute_uminus(instruction* instr)		{assert(0);}
void	execute_and(instruction* instr)			{assert(0);}
void	execute_or(instruction* instr)			{assert(0);}
void	execute_not(instruction* instr)			{assert(0);}
void	execute_jeq(instruction* instr);
void	execute_jne(instruction* instr);
void	execute_jle(instruction* instr);		
void	execute_jge(instruction* instr);			
void	execute_jlt(instruction* instr);			
void	execute_jgt(instruction* instr);			
void	execute_call(instruction* instr);
void	execute_pusharg(instruction* instr);
void	execute_funcenter(instruction* instr);
void	execute_funcexit(instruction* instr);
void	execute_newtable(instruction* instr)	{assert(0);}
void	execute_tablegetelem(instruction* instr){assert(0);}
void	execute_tablesetelem(instruction* instr){assert(0);}
void	execute_nop(instruction* instr)	{}
void	execute_jump(instruction* instr){
	pc = instr->result->val; 
}

typedef void (*execute_func_t) (instruction *);
execute_func_t executeFuncs[]={
	execute_assign,
	execute_add,
	execute_sub,
	execute_mul,
	execute_div,
	execute_mod,
	execute_uminus,
	execute_and,
	execute_or,
	execute_not,
	execute_jeq,
	execute_jne,
	execute_jle,
	execute_jge,
	execute_jlt,
	execute_jgt,
	execute_call,
	execute_pusharg,
	execute_funcenter,
	execute_funcexit,
	execute_newtable,
	execute_tablegetelem,
	execute_tablesetelem,
	execute_jump,
	execute_nop
};


unsigned                currInstruction = 0;
instruction*   			instructions = (instruction*)  0;



enum avm_memcell_t {
	number_m      =0,
	string_m      =1,
	bool_m        =2,
	table_m       =3,
	userfunc_m    =4,
	libfunc_m     =5,
	nil_m         =6,
	undef_m       =7
};
typedef enum avm_memcell_t avm_memcell_t;

struct avm_table;

struct avm_memcell {
	avm_memcell_t type;
	union {
			double numVal;
			char* strVal;
			unsigned char boolVal;
			struct avm_table* tableVal;
			unsigned funcVal;
			char* libfuncVal;
		} data;
};
typedef struct avm_memcell avm_memcell; 

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))

avm_memcell stack[AVM_STACKSIZE];

static void avm_initstack(void){
	unsigned i;
	for(i=0;i<AVM_STACKSIZE;i++)
	{
		AVM_WIPEOUT(stack[i]);
		stack[i].type=undef_m;
	}
}

#define AVM_STACKENV_SIZE 4
avm_memcell ax,bx,cx;
avm_memcell retval;
unsigned top,topsp;

double consts_getnumber (unsigned index){
	return numCosts[index];
}
char* consts_getstring(unsigned index){
	return stringConsts[index];
}
char* libfuncs_getused(unsigned index){
	return namedLibFuncs[index];
}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
	switch (arg->type){
		case global_a: return &stack[AVM_STACKSIZE-1-arg->val];

		case local_a: return  &stack[topsp-arg->val];

		case formal_a: return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];

		case retval_a: return &retval; 

		case number_a: {
			reg->type=number_m;
			reg->data.numVal = consts_getnumber(arg->val);
			return reg;
		}

		case string_a:{
			reg->type = string_m;
			reg->data.strVal = strdup(consts_getstring(arg->val));
			return reg;
		}

		case bool_a:{
			reg->type=bool_m;
			reg->data.boolVal = arg->val;
			return reg;
		}

		case nil_a: reg->type = nil_m; return reg;

		case userfunc_a : {
			reg->type = userfunc_m;
			reg->data.funcVal = arg->val;
			return reg;
		}

		case libfunc_a : {
			reg->type = libfunc_m;
			reg->data.libfuncVal = libfuncs_getused(arg->val);
			return reg;
		}

		default :  printf("\n\n%d\n\n", pc);assert(0);
	}

}

#define AVM_ENDING_PC codeSize
#define AVM_MAX_INSTRUCTIONS (unsigned)nop_v
void execute_cycle(void){
	if(executionFinished)
		exit(1);
	else
		if(pc == AVM_ENDING_PC){
		executionFinished = 1;
		return;
	}
	else{
		assert(pc < AVM_ENDING_PC);
		instruction* instr = code + pc;
		assert(
			instr->opcode >= 0 &&
			instr->opcode <= AVM_MAX_INSTRUCTIONS
		);
		if(instr->srcLine)
			currLine = instr->srcLine;
		unsigned oldPC =pc;
		(*executeFuncs[instr->opcode])(instr);
		if(pc == oldPC)
		++pc;
	}
}

void memclear_string (avm_memcell * m){
	assert(m->data.strVal);
	free(m->data.strVal);
}

void memclear_table(avm_memcell * m){
	assert(m->data.tableVal);
//	avm_tabledecrefcounter(m->data.tableVal);
}

typedef void (*memclear_func_t)(avm_memcell*);
memclear_func_t memclearFuncs[]={
	0,
	memclear_string,
	0,
	memclear_table,
	0,
	0,
	0,
	0
};




void avm_memcellclear ( avm_memcell* m ){
	if(m->type!=undef_m){
		memclear_func_t f = memclearFuncs[m->type];
		if(f)
			(*f)(m);
		m->type = undef_m;
	}
}

#include <stdarg.h>
void avm_warning(char* format,...){
	va_list valist;
	va_start(valist, format);
	fprintf(stderr, format, valist);
}


void avm_assign(avm_memcell* lv,avm_memcell* rv){
	if(lv == rv) return;

	if (lv->type == table_m &&
		rv->type == table_m &&
		lv->data.tableVal == rv->data.tableVal)

	if(rv->type == undef_m)
		avm_warning("assigning from 'undef' content!");

	avm_memcellclear(lv);
	memcpy(lv,rv,sizeof(avm_memcell));

	if(lv->type == string_m)
		lv->data.strVal = strdup(rv->data.strVal);
	//else if(lv->type == table_m)
		//avm_tableincrefcounter(lv->data.tableVal);

}

#define N 4096

void execute_assign(instruction * instr){
	avm_memcell * lv = avm_translate_operand(instr->result,(avm_memcell*)0);
	avm_memcell * rv = avm_translate_operand(instr->arg1,&ax);	

	//assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv==&retval));

	avm_assign(lv,rv);

}

void avm_error(char* format,...){
	va_list valist;
	va_start(valist, format);
	fprintf(stderr, format, valist);
	executionFinished=1;
}

void avm_dec_top(void){
	
	if(!top){
		avm_error("stack overflow");
		executionFinished = 1;
	}
	else
		--top;
}

void avm_push_envvalue(unsigned val){
	stack[top].type = number_m;
	stack[top].data.numVal=val;
	avm_dec_top();
}

unsigned totalActuals = 0;

void avm_callsaveenviroment(void){
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc + 1);
	avm_push_envvalue(top + totalActuals + 2);
	avm_push_envvalue(topsp);
}

/*
typedef void (*library_func_t) (void);
library_func_t avm_getlibraryfunc (char* id){
	if()


}*/

#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1

unsigned avm_get_envvalue  (unsigned i)	{
	assert (stack[i].type == number_m);
	unsigned val = (unsigned) stack[i].data.numVal;
	assert (stack[i].data.numVal == ((double) val));
	return val;
}

unsigned avm_totalactuals(void){
	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

char* number_tostring(avm_memcell* memcell){
	int num = 100;
	char *s = (char*)malloc(sizeof(char)*num);
	sprintf(s, "%f", memcell->data.numVal);
	char *ss = strdup(s);
	free(s);
	return ss;
}
char* string_tostring(avm_memcell* memcell){
	//int num = 100;
	//char *s = (char*)malloc(sizeof(char)*num);
	//sprintf(s, "%f", memcell->data.numVal);
	char *ss = strdup(memcell->data.strVal);
	//free(s);
	return ss;
}

char* bool_tostring(avm_memcell* memcell){
	int num = 100;
	char *s = (char*)malloc(sizeof(char)*num);
	if(memcell->data.boolVal)
		sprintf(s, "%s", "TRUE");
	else
		sprintf(s, "%s", "FALSE");
	char *ss = strdup(s);
	free(s);
	return ss;
}
char* table_tostring(avm_memcell* memcell){
	return 0;
}
char* userfunc_tostring(avm_memcell* memcell){
	int num = 100;
	char *s = (char*)malloc(sizeof(char)*num);
	sprintf(s, "%s", userFuncs[memcell->data.funcVal].id);
	char *ss = strdup(s);
	free(s);
	return ss;
}
char* libfunc_tostring(avm_memcell* memcell){
	//int num = 100;
	//char *s = (char*)malloc(sizeof(char)*num);
	//sprintf(s, "%f", memcell->data.numVal);
	char *ss = strdup(memcell->data.libfuncVal);
	//free(s);
	return ss;
}
char* nil_tostring(avm_memcell* memcell){
	int num = 100;
	char *s = (char*)malloc(sizeof(char)*num);
	sprintf(s, "%s", "nil");
	char *ss = strdup(s);
	free(s);
	return ss;
}
char* undef_tostring(avm_memcell* memcell){
	int num = 100;
	char *s = (char*)malloc(sizeof(char)*num);
	sprintf(s, "%s", "undef");
	char *ss = strdup(s);
	free(s);
	return ss;
}

typedef char*(*tostring_func_t)(avm_memcell*);

tostring_func_t tostringFuncs[]={
	number_tostring,
	string_tostring,
	bool_tostring,
	table_tostring,
	userfunc_tostring,
	libfunc_tostring,
	nil_tostring,
	undef_tostring
};

char* avm_tostring(avm_memcell *m){
	assert(m->type >= 0 && m->type <= undef_m);
	return(*tostringFuncs[m->type])(m);
}



avm_memcell* avm_getactual(unsigned i){
	assert(i < avm_totalactuals());
	return &stack[topsp + AVM_STACKENV_SIZE +1 +i];
}

userFunc* avm_getfuncinfo  (unsigned address){
	return &userFuncs[address];  
}


void execute_funcenter	(instruction* instr)  {
	avm_memcell* func = avm_translate_operand(instr->result, &ax);
	assert(func);
	//assert(pc == func->data.funcVal);	


	totalActuals = 0;
	userFunc* funcInfo = avm_getfuncinfo (func->data.funcVal) ;
	topsp = top;
	top = top -funcInfo->localSize;
}



void execute_funcexit	(instruction* unused)	{
	unsigned oldTop =top;
	top      = avm_get_envvalue (topsp	+	AVM_SAVEDTOP_OFFSET);
	pc       = avm_get_envvalue (topsp	+	AVM_SAVEDPC_OFFSET);
	topsp    = avm_get_envvalue (topsp + AVM_SAVEDTOPSP_OFFSET);

	while	(++oldTop	<=	top)
		avm_memcellclear(&stack[oldTop]);
}

char* typeStrings[] = {
	"number",
	"string",
	"bool",
	"table",
	"userfunc",
	"libfunc",
	"nil",
	"undef"
};


typedef void (*library_func_t)();

void libfunc_print (void){
	unsigned n = avm_totalactuals();
	unsigned i;
	for(i=0 ;i < n ;++i){
		char*s = avm_tostring(avm_getactual(i));
		puts(s);
		free(s);
	}
}

void libfunc_typeof(void){
	unsigned n = avm_totalactuals();

	if(n != 1)
		avm_error("one argument (not %d) expected in 'typeof'!", n);
	else{
		avm_memcellclear(&retval);
		retval.type = string_m;
		retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
	}
}

void libfunc_totalarguments (void){
	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);

	if(!p_topsp){
		avm_error("'totalarguments' called outside a function!");
		retval.type = nil_m;
	}else{
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
	}
}

void libfunc_argument (void){
	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);

	if(!p_topsp){
		avm_error("'argument' called outside a function!");
		retval.type = nil_m;
	}else{
		//unsigned n = avm_totalactuals();
		avm_memcell * cell = avm_getactual(0);
		unsigned n = cell->data.numVal;
		cell = &stack[p_topsp + AVM_NUMACTUALS_OFFSET + n + 1];

		if(cell->type == number_m){
			retval.type = number_m;
			retval.data.numVal = cell->data.numVal;
			return;
		}

		if(cell->type == string_m || cell->type == libfunc_m){
			retval.type = string_m;
			
			if(cell->type == string_m)
				retval.data.strVal = strdup(cell->data.strVal);
			else
				retval.data.libfuncVal = strdup(cell->data.libfuncVal);
			
			return;
		}

		if(cell->type == userfunc_m){
			retval.type = userfunc_m;
			retval.data.funcVal = cell->data.funcVal;
			return;
		}

		if(cell->type == bool_m){
			retval.type = bool_m;
			retval.data.boolVal = cell->data.boolVal;
			return;
		}

		if(cell->type == table_m){
			retval.type = table_m;
			retval.data.tableVal = cell->data.tableVal;
			return;
		}

		if(cell->type == nil_m){
			retval.type = nil_m;
			//retval.data.tableVal = cell->data.tableVal;
			return;
		}
		
	}
}

void avm_callibfunc (char* id) {
	library_func_t f =0;// = avm_getlibraryfunc(id);


	if(strcmp(id,"print")==0){
		f = libfunc_print;
	}

	if(strcmp(id,"argument")==0){
		f = libfunc_argument;
	}

	if(strcmp(id,"totalarguments")==0){
		f = libfunc_totalarguments;
	}

	if(strcmp(id,"typeof")==0){
		f = libfunc_typeof;
	}




	if  (!f)  {
		avm_error("unsupported lib func '%s' called!", id);
		executionFinished = 1;
	}
	else  {
		topsp = top ;
		totalActuals = 0;
		(*f)();
		if(!executionFinished)
			execute_funcexit((instruction*) 0);
	}

}

void execute_pusharg(instruction* instr){
	avm_memcell* arg = avm_translate_operand(instr->arg1, &ax);
	assert(arg);

	avm_assign(&stack[top], arg);
	++totalActuals;
	avm_dec_top();
}

void execute_call(instruction * instr){
	avm_memcell * func = avm_translate_operand(instr->arg1,&ax);
	assert(func);
	avm_callsaveenviroment();

	switch (func->type){
		case userfunc_m : {
			pc = userFuncs[func->data.funcVal].address;//func->data.funcVal;
			assert(pc<AVM_ENDING_PC);
			assert(code[pc].opcode == funcenter_v);
			break;
		}
		case string_m : avm_callibfunc(func->data.strVal); break;

		case libfunc_m : avm_callibfunc(func->data.libfuncVal); break;

		default : {
			char* s = avm_tostring(func);
			avm_error("call: cannot bind %s to function",s);
			free(s);
			executionFinished = 1;
		}
	}
}

void avm_initialize(void){
	avm_initstack();

	//avm_registerlibfunc("print", libfunc_print);
	//avm_registerlibfunc("typeof", libfunc_typeof);
}


typedef double (*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y){return x+y;}
double sub_impl(double x, double y){return x-y;}
double mul_impl(double x, double y){return x*y;}
double div_impl(double x, double y){return x/y;}
double mod_impl(double x, double y){return ((unsigned)x)%((unsigned)y);}

arithmetic_func_t arithmeticFuncs[] = {
	add_impl,
	sub_impl,
	mul_impl,
	div_impl,
	mod_impl
};

void execute_arithmetic(instruction* instr){
	avm_memcell* lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);


	assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv==&retval));
	assert(rv1 && rv2);	

	if(rv1->type != number_m || rv2->type != number_m){
		avm_error("not a number in arithmetic_!");
		executionFinished = 1;
	}else{
		arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
		avm_memcellclear(lv);
		lv->type 			= number_m;
		lv->data.numVal 	= (*op)(rv1->data.numVal, rv2->data.numVal);
	}
}

typedef unsigned char(*tobool_func_t)(avm_memcell*);

unsigned char number_tobool(avm_memcell* m){return m->data.numVal != 0;}
unsigned char string_tobool(avm_memcell* m){return m->data.strVal[0] != 0;}
unsigned char bool_tobool(avm_memcell* m){return m->data.boolVal;}
unsigned char table_tobool(avm_memcell* m){return 1;}
unsigned char userfunc_tobool(avm_memcell* m){return 1;}
unsigned char libfunc_tobool(avm_memcell* m){return 1;}
unsigned char nil_tobool(avm_memcell* m){return 0;}
unsigned char undef_tobool(avm_memcell* m){assert(0); return 0;}

tobool_func_t toboolFuncs[] = {
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
};

unsigned char avm_tobool(avm_memcell* m){
	assert(m->type >= 0 && m->type < undef_m);
	return (*toboolFuncs[m->type])(m);
}




void execute_jeq(instruction* instr){

	assert(instr->result->type == label_a);

	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1)) == (avm_tobool(rv2));
	else if(rv1->type != rv2->type)
		avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
	else{
		if(rv1->type == number_m){
			result = (rv1->data.numVal == rv2->data.numVal)?1:0;
		}else if(rv1->type == string_m){
			result = (strcmp(rv1->data.strVal,rv2->data.strVal)==0)?1:0;
		}else if(rv1->type == userfunc_m){
			result = (rv1->data.funcVal == rv2->data.funcVal)?1:0;
		}else if(rv1->type == libfunc_m){
			result = (strcmp(rv1->data.libfuncVal,rv2->data.libfuncVal)==0)?1:0;
		}else if(rv1->type == bool_m){
			result = (avm_tobool(rv1)) == (avm_tobool(rv2));
		}else{
			avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
		}
	}

	if(!executionFinished && result)
		pc = instr->result->val; 

}

void execute_jne(instruction* instr){

	assert(instr->result->type == label_a);

	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

	unsigned char result = 1;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1)) == (avm_tobool(rv2));
	else if(rv1->type != rv2->type)
		avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
	else{
		if(rv1->type == number_m){
			result = (rv1->data.numVal == rv2->data.numVal)?1:0;
		}else if(rv1->type == string_m){
			result = (strcmp(rv1->data.strVal,rv2->data.strVal)==0)?1:0;
		}else if(rv1->type == userfunc_m){
			result = (rv1->data.funcVal == rv2->data.funcVal)?1:0;
		}else if(rv1->type == libfunc_m){
			result = (strcmp(rv1->data.libfuncVal,rv2->data.libfuncVal)==0)?1:0;
		}else if(rv1->type == bool_m){
			result = (avm_tobool(rv1)) == (avm_tobool(rv2));
		}else{
			avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
		}
	}

	if(!executionFinished && result==0)
		pc = instr->result->val; 

}

void execute_jle(instruction* instr){

	assert(instr->result->type == label_a);

	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	//else if(rv1->type == nil_m || rv2->type == nil_m)
	//	result = rv1->type == nil_m && rv2->type == nil_m;
	//else if(rv1->type == bool_m || rv2->type == bool_m)
	//	result = (avm_tobool(rv1)) == (avm_tobool(rv2));
	else if(rv1->type != rv2->type)
		avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
	else{
		if(rv1->type == number_m){
			result = (rv1->data.numVal <= rv2->data.numVal)?1:0;
		}else {
			avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
		}
	}

	if(!executionFinished && result)
		pc = instr->result->val; 

}

void execute_jge(instruction* instr){

	assert(instr->result->type == label_a);

	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	//else if(rv1->type == nil_m || rv2->type == nil_m)
	//	result = rv1->type == nil_m && rv2->type == nil_m;
	//else if(rv1->type == bool_m || rv2->type == bool_m)
	//	result = (avm_tobool(rv1)) == (avm_tobool(rv2));
	else if(rv1->type != rv2->type)
		avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
	else{
		if(rv1->type == number_m){
			result = (rv1->data.numVal >= rv2->data.numVal)?1:0;
		}else {
			avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
		}
	}

	if(!executionFinished && result)
		pc = instr->result->val; 

}

void execute_jlt(instruction* instr){

	assert(instr->result->type == label_a);

	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	
	else if(rv1->type != rv2->type)
		avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
	else{
		if(rv1->type == number_m){
			result = (rv1->data.numVal < rv2->data.numVal)?1:0;
		}else {
			avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
		}
	}

	if(!executionFinished && result)
		pc = instr->result->val; 

}

void execute_jgt(instruction* instr){

	assert(instr->result->type == label_a);

	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");

	else if(rv1->type != rv2->type)
		avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
	else{
		if(rv1->type == number_m){
			result = (rv1->data.numVal > rv2->data.numVal)?1:0;
		}else {
			avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
		}
	}

	if(!executionFinished && result)
		pc = instr->result->val; 

}




int main(){

	//read binary file
	FILE *file = fopen("mpekas.abc", "rb+");
	if(file == NULL)
		return 1;
	int i;

	//diavazoume to magic number
	unsigned int magic;
	fread(&magic, sizeof(unsigned int), 1, file);

	if(magic==340200501){

		//diavazw posa strings exoume
		unsigned int total;// = totalStringConsts;
		fread(&total, sizeof(unsigned int), 1, file);
		totalStringConsts=total;

		stringConsts=(char**)malloc(totalStringConsts*sizeof(char *));

		//gia kathe ena string
		for(i=0;i<total;++i){
			//diavazoume posous xaraktires exei
			unsigned int total1;// = strlen(stringConsts[i]);
			fread(&total1, sizeof(unsigned int), 1, file);
			stringConsts[i] = (char*)malloc((1+total1)*sizeof(char));

			//kai tous xaraktires
			fread(stringConsts[i], sizeof(char), total1, file);
			stringConsts[i][total1]=0;
		}

		//diavazw posa numbers exoume
		
		fread(&total, sizeof(unsigned int), 1, file);
		totalNumCosts = total;
		numCosts=(double*)malloc(totalNumCosts*sizeof(double));

		//gia kathe ena number
		for(i=0;i<total;++i){
			//diavazoume to number
			fread(&numCosts[i], sizeof(double), 1, file);
		}

		//diavazw posa userfuncs exoume
		
		fread(&total, sizeof(unsigned int), 1, file);
		totalUserFuncs = total;
		userFuncs=(userFunc*)malloc(totalUserFuncs*sizeof(userFunc));

		//gia kathe ena number
		for(i=0;i<total;++i){
			//diavazoume to userfunc
			//total = strlen(stringConsts[i]);
			fread(&userFuncs[i].address, sizeof(unsigned int), 1, file);
			fread(&userFuncs[i].localSize, sizeof(unsigned int), 1, file);
			
			//diavazoume posous xaraktires exei
			unsigned int total1;// = strlen(userFuncs[i].id);
			fread(&total1, sizeof(unsigned int), 1, file);
			userFuncs[i].id = (char*)malloc((1+total1)*sizeof(char));

			//kai tous xaraktires
			fread(userFuncs[i].id, sizeof(char), total1, file);
			userFuncs[i].id[total1]=0;
		}


		//diavazw posa strings exoume
		fread(&total, sizeof(unsigned int), 1, file);
		totalNamedLibFuncs = total;
		namedLibFuncs=(char**)malloc(totalNamedLibFuncs*sizeof(char *));

		//gia kathe ena libfunc
		for(i=0;i<total;++i){
			//diavazoume posous xaraktires exei
			unsigned int total1;// = strlen(namedLibFuncs[i]);
			fread(&total1, sizeof(unsigned int), 1, file);
			namedLibFuncs[i] = (char*)malloc((1+total1)*sizeof(char));

			//kai tous xaraktires
			fread(namedLibFuncs[i], sizeof(char), total1, file);
			namedLibFuncs[i][total1]=0;
		}


		//diavazw posa instructions exoume
		fread(&total, sizeof(unsigned int), 1, file);
		codeSize = total;

		code = (instruction*)malloc(codeSize*sizeof(instruction));

		//gia kathe ena instruction
		for(i=0;i<total;++i){
			
			unsigned int total1;

			fread(&total1, sizeof(unsigned int), 1, file);
			code[i].opcode = total1;


			fread(&total1, sizeof(unsigned int), 1, file);
			if(total1==1){
				code[i].arg1 =  (vmarg*)malloc(sizeof(vmarg));
				/*fread(&total1, sizeof(unsigned int), 1, file);

				code[i].arg1->type = total1;

				fread(&total1, sizeof(unsigned int), 1, file);
				code[i].arg1->type = total1;
				*/
				fread(&code[i].arg1->type, sizeof(code[i].arg1->type), 1, file);
				fread(&code[i].arg1->val, sizeof(code[i].arg1->val), 1, file);

			}else{
				code[i].arg1 = NULL;
			}

			fread(&total1, sizeof(unsigned int), 1, file);
			if(total1==1){
				code[i].arg2 =  (vmarg*)malloc(sizeof(vmarg));
				
				fread(&code[i].arg2->type, sizeof(code[i].arg2->type), 1, file);
				fread(&code[i].arg2->val, sizeof(code[i].arg2->val), 1, file);
			}else{
				code[i].arg2 = NULL;
			}

			fread(&total1, sizeof(unsigned int), 1, file);
			if(total1==1){
				code[i].result =  (vmarg*)malloc(sizeof(vmarg));
				
				fread(&code[i].result->type, sizeof(code[i].result->type), 1, file);
				fread(&code[i].result->val, sizeof(code[i].result->val), 1, file);
			}else{
				code[i].result = NULL;
			}
		}

		unsigned programVarOffset=0;
		fread(&programVarOffset, sizeof(programVarOffset), 1, file);
		fclose(file);

		instructions=code;
		currInstruction=codeSize;

	

		avm_initialize();

		top = AVM_STACKSIZE-1-programVarOffset;
		topsp = AVM_STACKSIZE-1-programVarOffset;

		
		while(1){
			execute_cycle();
		}



	}else{
		printf("\nMagic Number Failed!\n");
	}

}