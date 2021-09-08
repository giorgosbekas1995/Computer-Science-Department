%{
		#include <stdio.h>
		#include <stdlib.h>
		#include <stdbool.h>

		#include <string.h>
		#include <assert.h> 

		#define LEVELS 1000
		
		int scope=0;
		int loopcounter=0;

		int yyerror (char* yaccProvidedMessage);
		int yylex (void);

		extern int yylineno;
		extern FILE *yyin, *yyout;
		extern char *yytext;

	enum scopespace_t{ 
		programvar,
		functionlocal,
		formalarg
	};

	typedef enum scopespace_t scopespace_t;

	enum symbol_t {var_s,programfunc_s,libraryfunc_s};
	
	typedef enum symbol_t symbol_t;


	struct returnlist{
		unsigned label;
		struct returnlist *next;
	};

	typedef struct symbol{
		bool isActive;
		symbol_t type;
		char* name;
		scopespace_t space;
		unsigned offset;
		unsigned scope;
		unsigned line;
		struct symbol *nextS;
		struct symbol *nextC;

		int iaddress;
		int taddress;
		int totallocals;

		//fasi4
		struct returnlist *returnList;
		int jump;
	}symbol;

	typedef struct symbol SymbolTableEntry;



	unsigned programVarOffset=0;
	unsigned functionLocalOffset=0;
	unsigned formalArgOffset=0;
	unsigned scopeSpaceCounter=1;

	scopespace_t currscopespace(void);
	unsigned currscopeoffset(void);
	void inccurrscopeoffset (void);
	void enterscopespace (void);
	void exitscope(void);

	// synartiseis deyteris fasis

	SymbolTableEntry *BUCKETS[LEVELS];	
	SymbolTableEntry *SCOPELISTS[LEVELS];

	int isLibrary(const char *a);
	unsigned int SymTable_hash(const char *pcKey);
	
	void insert(const char *name,symbol_t type, scopespace_t space, unsigned offset);//,enum SymbolTableType type);
	void insert2(SymbolTableEntry*);//,enum SymbolTableType type);
	
	SymbolTableEntry* lookupScope(char* name, int scope);
	void hide(int scope);
	void addLibrary(const char *a);
	void printfHashTable();

	// synartiseis structs enums triti fasi
	enum iopcode{
		assign,
		add,
		sub,
		mul,
		diV,
		mod,
		uminus,
		and,
		or,
		not,
		if_eq,
		if_noteq,
		if_lesseq,
		if_greatereq,
		if_less,
		if_greater,
		call,
		param,
		ret,
		getretval,
		funcstart,
		funcend,
		tablecreate,
		tablegetelem,
		tablesetelem,
		jump
	};
	typedef enum iopcode iopcode;

	struct expr;
	
	typedef struct expr expr;
    
    struct quad{
		iopcode op;
		expr* result;
		expr* arg1;
		expr* arg2;
		unsigned label;
		unsigned line;

		unsigned taddress;
	};
	
	typedef struct quad quad;
	quad* quads=(quad*)0;
	unsigned total=0;
	unsigned int currQuad=0;

	#define EXPAND_SIZE 1024
	#define CURR_SIZE (total*sizeof(quad))
	#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

	void expand (void) {
		assert(total==currQuad);
		quad* p = (quad*) malloc(NEW_SIZE);
		if(quads){
			memcpy(p,quads, CURR_SIZE);
			free(quads);
		}
		quads=p;
		total += EXPAND_SIZE;
	}

	void emit_label(iopcode op,expr* arg1,expr* arg2,expr* result,unsigned label,unsigned line){

		if(currQuad == total)
			expand();

		quad* p =quads+currQuad++;
		p->arg1=arg1;
		p->arg2=arg2;
		p->result=result;
		p->label=label;
		p->line=line;
		p->op =op;

	}

	void emit(iopcode op,expr* arg1,expr* arg2,expr* result,unsigned line){

		if(currQuad == total)
			expand();

		quad* p =quads+currQuad++;
		p->arg1=arg1;
		p->arg2=arg2;
		p->result=result;
		//p->label=label;
		p->line=line;
		p->op =op;

	}

	enum expr_t {
		var_e,
		tableitem_e,

		programfunc_e,
		libraryfunc_e,

		arithexpr_e,
		boolexpr_e,
		assignexpr_e,
		newtable_e,

		constnum_e,
		constbool_e,
		conststring_e,

		nil_e
	};

	typedef enum expr_t expr_t;

	typedef struct expr{
		expr_t 			type;
		symbol* 		sym;
		expr* 			index;
		double 			numConst;
		char* 			strConst;
		unsigned char 	boolConst;
		expr* 			next;
	}expr;

	void printICODE();
	void printFCODE();

	expr* lvalue_expr(symbol* sym){
		assert(sym);
		expr* e = (expr*)malloc(sizeof(expr));
		memset(e, 0, sizeof(expr));

		e->next = (expr*) 0;
		e->sym = sym;	

		switch (sym->type){
			case var_s 			: e->type = var_e; break;
			case programfunc_s 	: e->type = programfunc_e; break;
			case libraryfunc_s 	: e->type = libraryfunc_e; break;
			default 			: assert(0);
		}
		return e;
	}

	unsigned nextquadlabel(void){
		return currQuad;
	}

	expr* newexpr(expr_t t){
		expr* e = (expr*)malloc(sizeof(expr));
		memset(e, 0, sizeof(expr));
		e->type = t;
		return e;
	}

	expr* newexpr_constnum(double i){
		expr* e = newexpr(constnum_e);
		e->numConst = i;
		return e;
	}

	expr* newexpr_conststring(char* s){
		expr* e = newexpr(conststring_e);
		e->strConst = strdup(s);
		return e;
	}

	expr* newexpr_constbool(bool b){
		expr* e = newexpr(constbool_e);
		e->boolConst = b;
		return e;
	}

	SymbolTableEntry* newsymbol( const char *name, symbol_t type, scopespace_t space, unsigned offset){
		
		SymbolTableEntry *x = malloc(sizeof (SymbolTableEntry));
		x->isActive=true;
		x->name=strdup(name);
		x->scope=scope;
		x->line=yylineno;
		x->type=type;
		x->space=space;
		x->offset=offset;
		inccurrscopeoffset();

		return x;
	}

	int tempcounter = 0;
	symbol* newtemp() {
		char* name = malloc(10);
		sprintf(name, "%s%d", "_t", tempcounter++);
		symbol *sym = lookupScope(name, scope);
			
		if (sym == NULL) { 
			SymbolTableEntry* entry = newsymbol(name, var_s,  currscopespace(), currscopeoffset() );
			insert2(entry);
			return entry;			
		}else
			return sym;
	}

	expr* emit_iftableitem(expr* e){
		if(e->type != tableitem_e)
			return e;
		else{
			expr* result = newexpr(var_e);
			result->sym = newtemp();
			emit(tablegetelem,
				e,
				e->index,
				result, yylineno);
			return result;	
		}
	}

	expr* logbool(enum iopcode op, expr *e1, expr* e2){
		expr* e = newexpr(boolexpr_e);
		e->sym = newtemp();
		emit(op, e1, e2, e, yylineno);
		return e;
	}
	
	expr* relbool(enum iopcode op, expr *e1, expr* e2){
		expr* e = newexpr(boolexpr_e);
		e->sym = newtemp();
		emit_label(op, e1, e2, NULL, currQuad+3, yylineno);
		emit(assign, newexpr_constbool(false), NULL, e, yylineno);
		emit_label(jump, NULL, NULL, NULL, currQuad+2, yylineno);
		emit(assign, newexpr_constbool(true), NULL, e, yylineno);
		return e;
	}

	expr* arithmetic(enum iopcode op, expr* e1, expr* e2){
		expr* e = newexpr(arithexpr_e);
		e->sym = newtemp();
		emit(op, e1, e2, e, yylineno);
		return e;
	}

	void checkuminus(expr* e){
		if(e->type == constbool_e 		||
			e->type == conststring_e	||
			e->type == nil_e 			||
			e->type == newtable_e 		||
			e->type == programfunc_e 	||
			e->type == libraryfunc_e 	||
			e->type == boolexpr_e)
			yyerror("Illegal expr to unary -");
	}

	void patchlabel(unsigned quadNo, unsigned label){
		assert(quadNo < currQuad);
		quads[quadNo].label = label;
	}


	unsigned int istempname(char* s)
	{
		return *s == '_';
	}

	unsigned int istempexpr(expr* e){
		return e->sym && e->sym->type == var_s && istempname(e->sym->name);
	}

	/// generic list start

	struct Element{
		void *data;
		struct Element *next;
	};

	struct List{
		struct Element *head;
		struct Element *tail;
		int count;
	};

	void push_last(struct List* list, struct Element *element){
		element->next = NULL;
		
		if(list->head == NULL){
			list->head = element;
			list->tail = element;
		}else{
			list->tail->next = element;
			list->tail = element;
		}
		list->count++;
	}

	void push_first(struct List* list, struct Element *element){
		element->next = NULL;
		
		if(list->head == NULL){
			list->head = element;
			list->tail = element;
		}else{
			element->next = list->head;
			list->head = element;
			//list->tail->next = element;
			//list->tail = element;
		}
		list->count++;
	}

	void* pop(struct List* list){
		if(list->head == NULL)
			return NULL;
		list->count--;
		struct Element* e = list->head->data;
		list->head=list->head->next;
		if(list->head == NULL)
			list->tail = NULL;
		return  e;
	}

	void* top(struct List* list){
		if(list->head == NULL)
			return NULL;
		struct Element* e = list->head->data;
		return  e;
	}

	

	//////////////////////////////////////////////////////////////////////////////
	struct functionLocalOffsetStruct{
		int functionLocalOffset;
	};

	struct Element* makeFunctionLocalOffsetStruct(int functionLocalOffset){
		struct Element* e = malloc(sizeof(struct Element));
		e->data = malloc(sizeof(struct functionLocalOffsetStruct));

		((struct functionLocalOffsetStruct*)e->data)->functionLocalOffset = functionLocalOffset;

		return e;
	}

	int getFunctionLocalOffset(void *elem){
		if(elem == NULL) return -1;
		return ((struct functionLocalOffsetStruct*)elem)->functionLocalOffset;
	}

	struct List functionLocalsStack;
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	struct loopcounterStruct{
		int loopcounter;
	};

	struct Element* makeLoopcounterStruct(int loopcounter){
		struct Element* e = malloc(sizeof(struct Element));
		e->data = malloc(sizeof(struct loopcounterStruct));

		((struct loopcounterStruct*)e->data)->loopcounter = loopcounter;

		return e;
	}

	int getLoopcounter(void *elem){
		if(elem == NULL) return -1;
		return ((struct loopcounterStruct*)elem)->loopcounter;
	}

	struct List loopcounterStack;
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	struct ElistStruct{
		expr * k;
	};

	struct Element* makeElistStruct(expr * k){
		struct Element* e = malloc(sizeof(struct Element));
		e->data = malloc(sizeof(struct ElistStruct));

		((struct ElistStruct*)e->data)->k = k;

		return e;
	}

	expr * getElist(void *elem){
		if(elem == NULL) return NULL;
		return ((struct ElistStruct*)elem)->k;
	}


	struct List ElistStack;
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	struct IndexedStruct{
		expr * k1;
		expr * k2;
	};

	struct Element* makeIndexedStruct(expr * k1,expr * k2){
		struct Element* e = malloc(sizeof(struct Element));
		e->data = malloc(sizeof(struct IndexedStruct));

		((struct IndexedStruct*)e->data)->k1 = k1;
		((struct IndexedStruct*)e->data)->k2 = k2;

		return e;
	}

	/*expr * getIndexed(void *elem){
		if(elem == NULL) return NULL;
		return ((struct IndexedStruct*)elem)->k1;
		return ((struct IndexedStruct*)elem)->k2;
	}*/


	struct List IndexedStack;

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	struct BreakStruct{
		int i;int l;
	};

	struct Element* makeBreakStruct(int i){
		struct Element* e = malloc(sizeof(struct Element));
		e->data = malloc(sizeof(struct BreakStruct));

		((struct BreakStruct*)e->data)->i = i;
		((struct BreakStruct*)e->data)->l = loopcounter;

		return e;
	}

	int getBreakI(void *elem){
		if(elem == NULL) return -1;
		return ((struct BreakStruct*)elem)->i;
	}

	int getBreakL(void *elem){
		if(elem == NULL) return -1;
		return ((struct BreakStruct*)elem)->l;
	}

	struct List BreakStack;
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	struct ContinueStruct{
		int i;int l;
	};

	struct Element* makeContinueStruct(int i){
		struct Element* e = malloc(sizeof(struct Element));
		e->data = malloc(sizeof(struct ContinueStruct));

		((struct ContinueStruct*)e->data)->i = i;
		((struct ContinueStruct*)e->data)->l = loopcounter;

		return e;
	}

	int getContinueI(void *elem){
		if(elem == NULL) return -1;
		return ((struct ContinueStruct*)elem)->i;
	}

	int getContinueL(void *elem){
		if(elem == NULL) return -1;
		return ((struct ContinueStruct*)elem)->l;
	}

	struct List ContinueStack;
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	struct IncompleteStruct{
		int x; int y;
	};

	struct Element* makeIncompleteStruct(int x, int y){
		struct Element* e = malloc(sizeof(struct Element));
		e->data = malloc(sizeof(struct IncompleteStruct));

		((struct IncompleteStruct*)e->data)->x = x;
		((struct IncompleteStruct*)e->data)->y = y;

		return e;
	}

	int getIncompleteX(void *elem){
		if(elem == NULL) return -1;
		return ((struct IncompleteStruct*)elem)->x;
	}

	int getIncompleteY(void *elem){
		if(elem == NULL) return -1;
		return ((struct IncompleteStruct*)elem)->y;
	}

	struct List IncompleteStructStack;
	//////////////////////////////////////////////////////////////////////////////
	
	struct userFuncStruct{
		symbol *sss;
	};

	struct Element* makeUserFuncStruct(symbol * sss){
		struct Element* e = malloc(sizeof(struct Element));
		e->data = malloc(sizeof(struct IncompleteStruct));

		
		((struct userFuncStruct*)e->data)->sss = sss;
		
		

		return e;
	}

	symbol*  getUserFuncSymbol(void *elem){
		if(elem == NULL) return NULL;
		return ((struct userFuncStruct*)elem)->sss;
	}


	struct List UserFuncStack;
	
	//////////////////////////////////////////////////////////////////////////////

	void initLists(){
		functionLocalsStack.head = functionLocalsStack.tail = NULL;
		functionLocalsStack.count = 0;

		loopcounterStack.head = loopcounterStack.tail = NULL;
		loopcounterStack.count = 0;

		ElistStack.head = ElistStack.tail = NULL;
		ElistStack.count = 0;

		IncompleteStructStack.head = IncompleteStructStack.tail = NULL;
		IncompleteStructStack.count = 0;

		//UserFuncStack.head = UserFuncStack.tail = NULL;
		//UserFuncStack.count = 0;
	}


	/// generic list end


	expr* make_call(expr* lvalue, expr* nil){
		expr* func = emit_iftableitem(lvalue);
		//for (each arg in reversed elist){
		//	emit(param, arg);
		//}

		expr* arg;
		while( (arg = getElist(pop(&ElistStack)) )!= NULL ){
			emit(param, arg, NULL, NULL, yylineno);
		}
		
		emit(call, func, NULL, NULL, yylineno);
		expr* result = newexpr(var_e);
		result->sym = newtemp();
		emit(getretval, result, NULL, NULL, yylineno);
		
		return result;
	}


	void enterscopespace (void);

	void exitscopespace(void);

	void resetformalargsoffset(void){
		formalArgOffset = 0;
	}

	void resetfunctionlocaloffset(void){
		functionLocalOffset = 0;
	}

	void restorecurrentscopeoffset(unsigned n){
		switch (currscopespace()){
			case	programvar		: programVarOffset = n; break;
			case functionlocal 		: functionLocalOffset = n; break;
			case formalarg 			: formalArgOffset = n; break;
			default 				: assert(0);
		}
	}

	struct forr{
		int enter, test;
	};

	struct callsu{
		bool method;
		char * name;
	};


	expr * member_item(expr * lvalue,char * name){
		lvalue = emit_iftableitem(lvalue);
		expr* item = newexpr(tableitem_e);
		item->sym = lvalue->sym;
		item->index = newexpr_conststring(name);
		return item;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////// FASI 4 

	#include "tcode.h"
	unsigned consts_newstring(char* s){
		int i;
		if(totalStringConsts == 0){
			stringConsts = malloc(sizeof(char *));
			stringConsts[totalStringConsts++] = s;
			return 0;
		}else{
			i=totalStringConsts-1;
			while(i>=0){
				if(strcmp(stringConsts[i],s)==0)
					return i;
				--i;
			}
			stringConsts = realloc(stringConsts, (totalStringConsts+1)*sizeof(char *));
			stringConsts[totalStringConsts++] = s;
			return totalStringConsts-1;
		}
	}


	unsigned consts_newnumber(double n){
		int i;
		if(totalNumCosts == 0){
			numCosts = malloc(sizeof(double));
			numCosts[totalNumCosts++] = n;
			return 0;
		}else{
			i=totalNumCosts-1;
			while(i>=0){
				if(numCosts[i] == n)
					return i;
				--i;
			}
			numCosts = realloc(numCosts, (totalNumCosts+1)*sizeof(double));
			numCosts[totalNumCosts++] = n;
			return totalNumCosts-1;
		}
	}


	unsigned libfuncs_newused(char* s){
		int i;
		if(totalNamedLibFuncs == 0){
			namedLibFuncs = malloc(sizeof(char *));
			namedLibFuncs[totalNamedLibFuncs++] = s;
			return 0;
		}else{
			i=totalNamedLibFuncs-1;
			while(i>=0){
				if(strcmp(namedLibFuncs[i],s)==0)
					return i;
				--i;
			}
			namedLibFuncs = realloc(namedLibFuncs, (totalNamedLibFuncs+1)*sizeof(char *));
			namedLibFuncs[totalNamedLibFuncs++] = s;
			return totalNamedLibFuncs-1;
		}
	}



	unsigned userfuncs_newfunc(symbol * f){
		int i;
		if(totalUserFuncs == 0){
			userFuncs = malloc(sizeof(userFunc));
			
			userFuncs[totalUserFuncs].address = f->taddress;
			userFuncs[totalUserFuncs].localSize = f->totallocals;
			userFuncs[totalUserFuncs++].id = f->name;

			//userFuncs[totalUserFuncs++] = *sym;
			return 0;
		}else{
			i=totalUserFuncs-1;
			while(i>=0){
				if(strcmp(userFuncs[i].id,f->name)==0 && userFuncs[i].address == f->taddress)
					return i;
				--i;
			}

			userFuncs = realloc(userFuncs, (totalUserFuncs+1)*sizeof(userFunc));

			userFuncs[totalUserFuncs].address = f->taddress;
			userFuncs[totalUserFuncs].localSize = f->totallocals;
			userFuncs[totalUserFuncs++].id = f->name;

			//userFuncs[totalUserFuncs++] = *sym;
			return totalUserFuncs-1;
		}
	}

	vmarg* make_operand(expr* e){
		
		vmarg* arg = malloc(sizeof(struct vmarg));

		switch (e->type){

			case var_e:
			case tableitem_e:
			case arithexpr_e:
			case boolexpr_e:
			case assignexpr_e:
			case newtable_e: 
			
				assert(e->sym);
				arg->val = e->sym->offset;

				switch(e->sym->space)
				{
					case programvar: arg->type = global_a; break;
					case functionlocal: arg->type = local_a; break;
					case formalarg: arg->type = formal_a; break;
					default : assert(0);
				}
				break;

			case constbool_e: 
				arg->val = e->boolConst;
				arg->type = bool_a;
				break;

			case conststring_e : 
				arg->val = consts_newstring(e->strConst);
				arg->type = string_a; 
				break;
			
			case constnum_e: 
				arg->val = consts_newnumber(e->numConst);
				arg->type = number_a;
				break;

			case programfunc_e : 
				arg->type = userfunc_a;
				//arg->val = e->sym->taddress;
				arg->val = userfuncs_newfunc(e->sym);
				break;
			
			case libraryfunc_e : 
				arg->type = libfunc_a;
				arg->val = libfuncs_newused(e->sym->name);
				break;
			
			case nil_e: 
				arg->type = nil_a; 
				break;

			default: assert(0);

		}

		return arg;

	}


	vmarg* make_numberopearand (double val){
		vmarg* arg = malloc(sizeof(struct vmarg));
		arg->val = consts_newnumber(val);
		arg->type = number_a;
		return arg;
	}

	vmarg* make_booloperand (unsigned val){
		vmarg* arg = malloc(sizeof(struct vmarg));
		arg->val = val ;
		arg->type = bool_a;
		return arg;
	}

	vmarg* make_retvaloperand (){
		vmarg* arg = malloc(sizeof(struct vmarg));
		arg->type = retval_a;
		return arg;
	}


	incomplete_jump * ij_head = (incomplete_jump*)0;
	unsigned ij_total = 0;

	instruction* instructions=NULL;
	int totalInstructions=0;
	int currInstruction=0;

	#define CCURR_SIZE (totalInstructions*sizeof(instruction))
	#define NNEW_SIZE (EXPAND_SIZE*sizeof(instruction)+CCURR_SIZE)


	void ppatchlabel(unsigned No, unsigned label){
		assert(No < currInstruction);
		instructions[No].result->val = label;
	}

	void eexpand (void) {
		assert(totalInstructions==currInstruction);
		instruction* p = (instruction*) malloc(NNEW_SIZE);
		if(instructions){
			memcpy(p,instructions, CCURR_SIZE);
			free(instructions);
		}
		instructions=p;
		totalInstructions += EXPAND_SIZE;
	}

	
	void eemit(instruction t){

		if(currInstruction == totalInstructions)
			eexpand();

		instruction* p =instructions+currInstruction++;
	
		p->arg1=t.arg1;
		p->arg2=t.arg2;
		p->result=t.result;
		//p->label=t.label;
		//p->line=t.line;
		p->opcode = t.opcode;
	}

	int nextinstructionlabel(){
		return currInstruction;
	}
	quad * CURRENTQUAD;
	void ggenerate(vmopcode op,quad quad) {
		
		instruction t;
		t.opcode = op;

		if(quad.arg1==NULL)t.arg1=NULL;
		else t.arg1 = make_operand(quad.arg1);

		if(quad.arg2==NULL)t.arg2=NULL;
		else t.arg2 = make_operand(quad.arg2);

		if(quad.result==NULL)t.result=NULL;
		else t.result = make_operand(quad.result);


		//make_operand(quad.arg2,&t.arg2);
		//make_operand(quad.result,&t.result);
		CURRENTQUAD->taddress = nextinstructionlabel();
		eemit(t);
	}

	void generate_ADD(quad quad)     {ggenerate(add_v,quad);}
	void generate_SUB(quad quad)     {ggenerate(sub_v,quad);}
	void generate_MUL(quad quad)     {ggenerate(mul_v,quad);}
	void generate_DIV(quad quad)     {ggenerate(div_v,quad);}
	void generate_MOD(quad quad)     {ggenerate(mod_v,quad);}

	void generate_NEWTABLE(quad quad)       	{ggenerate(newtable_v,quad);}
	void generate_TABLEGETELEM(quad quad)     	{ggenerate(tablegetelem_v,quad);}
	void generate_TABLESETELEM(quad quad)     	{ggenerate(tablesetelem_v,quad);}
	void generate_ASSIGN(quad quad)				{ggenerate(assign_v ,quad);}
	void generate_NOP()							{
		instruction t; 
		t.arg1 = t.arg2 = t.result = NULL;
		t.opcode = nop_v; 
		eemit(t);
	}

	int currprocessedquadd;

	int currprocessedquad(){
		return currprocessedquadd;
	}

	void generate_relational(vmopcode op,quad quad) {
		instruction t;
		t.opcode = op;
	

		if(quad.arg1==NULL)t.arg1=NULL;
		else t.arg1 = make_operand(quad.arg1);

		if(quad.arg2==NULL)t.arg2=NULL;
		else t.arg2 = make_operand(quad.arg2);

		t.result = malloc(sizeof(struct vmarg));
		
		t.result->type = label_a;

		if (quad.label < currprocessedquad() ){ 
			t.result->val = quads[quad.label].taddress;
		}else{
			//add_incomplete_jump(nextinstructionlabel(),quad.label);
			push_last(&IncompleteStructStack, makeIncompleteStruct(nextinstructionlabel(), quad.label)); 
		}
		CURRENTQUAD->taddress = nextinstructionlabel();
		eemit(t);
		
	}

	void generate_JUMP(quad quad)      		{ generate_relational(jump_v,quad); }
	void generate_IF_EQ(quad quad)     		{ generate_relational(jeq_v,quad); }
	void generate_IF_NOTEQ(quad quad)  		{ generate_relational(jne_v,quad); }
	void generate_IF_GREATER(quad quad) 	{ generate_relational(jgt_v,quad); }
	void generate_IF_GREATEREQ(quad quad)  	{ generate_relational(jge_v,quad); }
	void generate_IF_LESS(quad quad)     	{ generate_relational(jlt_v,quad); }
	void generate_IF_LESSEQ(quad quad)   	{ generate_relational(jle_v,quad); }



	void generate_AND(quad quad) {

		CURRENTQUAD->taddress = nextinstructionlabel();
		instruction t;
		t.opcode = jeq_v;
		t.arg1=make_operand(quad.arg1);
		t.arg2=make_booloperand(0);
		t.result = malloc(sizeof(struct vmarg));
		t.result->type = label_a;
		t.result->val = nextinstructionlabel()+4;
		eemit(t);
		
		
		t.arg1=make_operand(quad.arg2);
		t.result->val = nextinstructionlabel()+3;
		eemit(t);

		t.opcode = assign_v;
		t.arg1=make_booloperand(1);
		t.arg2=0;
		t.result=make_operand(quad.result);
		eemit(t);

		t.opcode = jump_v;
		t.arg1=0;
		t.arg2=0;
		t.result = malloc(sizeof(struct vmarg));
		t.result->type = label_a;
		t.result->val = nextinstructionlabel()+2;
		eemit(t);

		t.opcode = assign_v;
		t.arg1=make_booloperand(0);
		t.arg2=0;
		t.result=make_operand(quad.result);
		eemit(t);

	}
	void generate_OR(quad quad) {
		
		CURRENTQUAD->taddress = nextinstructionlabel();
		instruction t;
		t.opcode = jeq_v;
		t.arg1=make_operand(quad.arg1);
		t.arg2=make_booloperand(1);
		t.result = malloc(sizeof(struct vmarg));
		t.result->type = label_a;
		t.result->val = nextinstructionlabel()+4;
		eemit(t);
	
		
		
		t.arg1=make_operand(quad.arg2);
		t.result->val = nextinstructionlabel()+3;
		eemit(t);

		t.opcode = assign_v;
		t.arg1=make_booloperand(0);
		t.arg2=0;
		t.result=make_operand(quad.result);
		eemit(t);

		t.opcode = jump_v;
		t.arg1=0;
		t.arg2=0;
		t.result = malloc(sizeof(struct vmarg));
		t.result->type = label_a;
		t.result->val = nextinstructionlabel()+2;
		eemit(t);

		t.opcode = assign_v;
		t.arg1=make_booloperand(1);
		t.arg2=0;
		t.result=make_operand(quad.result);
		eemit(t);
	}

	void generate_NOT(quad quad) {
	 
		CURRENTQUAD->taddress = nextinstructionlabel();
		instruction t;
		
		t.opcode = jeq_v;
		t.arg1=make_operand(quad.arg1);
		t.arg2=make_booloperand(0);

		t.result = malloc(sizeof(struct vmarg));
		t.result->type = label_a;
		t.result->val = nextinstructionlabel()+3;
		eemit(t);

		t.opcode = assign_v;
		t.arg1=make_booloperand(0);
		t.arg2=0;
		t.result=make_operand(quad.result);
		eemit(t);

		t.opcode = jump_v;
		t.arg1=0;
		t.arg2=0;
		
		t.result = malloc(sizeof(struct vmarg));
		t.result->type = label_a;
		t.result->val = nextinstructionlabel()+2;
		eemit(t);

		t.opcode = assign_v;
		t.arg1=make_booloperand(1);
		t.arg2=0;
		t.result=make_operand(quad.result);
		eemit(t);

	}

	void generate_UMINUS(quad quad) {
		
		quad.arg2 = newexpr_constnum(-1);
		//quad.opcode = mul_v;

		ggenerate(mul_v,quad);
	}

	void generate_CALL(quad quad) {

		CURRENTQUAD->taddress = nextinstructionlabel();
		
		instruction t;
		t.opcode = call_v;
		t.arg1 = make_operand(quad.arg1);
		t.arg2 = t.result = 0;
		eemit(t);
	}

	void generate_PARAM(quad quad) {
		
		CURRENTQUAD->taddress= nextinstructionlabel();
		
		instruction t;
		t.opcode=pusharg_v;
		t.arg1 = make_operand(quad.arg1);
		t.arg2 = t.result = 0;
		eemit(t);
	}
	
	void generate_RETURN(quad quad) {

		CURRENTQUAD->taddress = nextinstructionlabel();
		
		instruction t;

		t.opcode = assign_v;
		
		t.result = make_retvaloperand();
		
		t.arg1 = make_operand(quad.arg1);

		t.arg2 = 0;
		eemit(t);

		///////////////////////////////////////////////////////////////////////////////////
		symbol *f = getUserFuncSymbol(top(&UserFuncStack));
		struct returnlist *r = (struct returnlist*)malloc(sizeof(struct returnlist));
		r->label = nextinstructionlabel();
		r->next = f->returnList;
		f->returnList = r;
		//append(f->returnList,nextinstructionlabel());
		///////////////////////////////////////////////////////////////////////////////////

		t.opcode = jump_v;
		t.arg1 = 0;
		t.arg2 = 0;
		t.result = malloc(sizeof(struct vmarg));
		t.result->type= label_a;
		eemit(t);
	}

	void generate_GETRETVAL(quad quad){

		CURRENTQUAD->taddress = nextinstructionlabel();
		
		instruction t;
		t.opcode = assign_v;
		t.result = make_operand(quad.arg1);
		t.arg1 = make_retvaloperand();
		t.arg2=0;
		eemit(t);

	}

	void generate_FUNCSTART(quad quad){

		symbol *f=quad.result->sym;

		///// i jump panw apo to funcstart
		instruction t1;
		t1.opcode = jump_v;
		t1.arg1 = t1.arg2 = 0;
		t1.result = malloc(sizeof(struct vmarg));
		f->jump=nextinstructionlabel();
		eemit(t1);
		/////
		
		f->taddress = nextinstructionlabel();
		CURRENTQUAD->taddress = nextinstructionlabel();

		//userfunctions.add(f->id,f->taddress,f->totallocals);
		userfuncs_newfunc(f);

		push_first(&UserFuncStack, makeUserFuncStruct(f)); 

		instruction t;
		
		t.opcode = funcenter_v;
		t.arg1=0;
		t.arg2=0;

		
		t.result = make_operand(quad.result);
		eemit(t);
	}

	
	void generate_FUNCEND(quad quad) {
		
		///////////////////////////////////////////////////////////////////////////////////
		//backpatch(f->returnlist, nextinstructionlabel())
		symbol *f = getUserFuncSymbol(pop(&UserFuncStack));

		struct returnlist *r = f->returnList;
		while(r!=NULL){
			ppatchlabel(r->label, nextinstructionlabel());r=r->next;
		}
		///////////////////////////////////////////////////////////////////////////////////

		CURRENTQUAD->taddress = nextinstructionlabel();
		ppatchlabel(f->jump, nextinstructionlabel()+1);

		instruction t;
		
		t.opcode = funcexit_v;
		t.arg1=0;
		t.arg2=0;

		t.result = make_operand(quad.result);
		eemit(t);
	}		
	typedef void(*generator_func_t)(quad);

	generator_func_t generators[] = {
		generate_ASSIGN,
		generate_ADD,
		generate_SUB,
		generate_MUL,
		generate_DIV,
		generate_MOD,
		generate_UMINUS,
		generate_AND,
		generate_OR,
		generate_NOT,
		generate_IF_EQ,
		generate_IF_NOTEQ,
		generate_IF_LESSEQ,
		generate_IF_GREATEREQ,
		generate_IF_LESS,
		generate_IF_GREATER,
		generate_CALL,
		generate_PARAM,
		generate_RETURN,
		generate_GETRETVAL,
		generate_FUNCSTART,
		generate_FUNCEND,
		generate_NEWTABLE,
		generate_TABLEGETELEM,
		generate_TABLESETELEM,
		generate_JUMP,
		generate_NOP
	};

	void generate (void){
		unsigned i;
		for(i=0; i<nextquadlabel(); i++){
			CURRENTQUAD = &quads[i];
			(*generators[quads[i].op])(quads[i]);
			currprocessedquadd=i;
		}

	}

	//////////////////////////////////////////////////////////////////////////


%}

%start program

%union{

	int intVal;
	double realVal;
	char* strVal;
	struct expr* exprNode; 
	struct symbol* symbolNode;

	struct forr* forrNode;
	struct callsu* callsuNode;

}
		
%token <intVal> INTCONST 	
%token <realVal> REALCONST  
%token <strVal> IDENT 

%token <strVal>	STRING

%token <strVal> IF 
%token <strVal> ELSE
%token <strVal> WHILE
%token <strVal> FOR
%token <strVal> FUNCTION 
%token <strVal> RETURN
%token <strVal> BREAK 
%token <strVal> CONTINUE
%token <strVal> AND 
%token <strVal> NOT
%token <strVal> OR
%token <strVal> LOCAL
%token <strVal> TRUE 
%token <strVal> FALSE
%token <strVal> NIL 			
%token <strVal> ASSIGN
%token <strVal> PLUS
%token <strVal> MINUS 
%token <strVal> MUL
%token <strVal> DIV
%token <strVal> MOD
%token <strVal> EQUALS
%token <strVal> DIFF 
%token <strVal> PLUSPLUS
%token <strVal> MINUSMINUS
%token <strVal> GREATER 				
%token <strVal> LESS 					
%token <strVal> GREATEREQ				
%token <strVal> LESSEREQ 				
%token <strVal> LEFTBRACE 				
%token <strVal> RIGHTBRACE 				
%token <strVal> LEFTBRACKET 			
%token <strVal> RIGHTBRACKET 			
%token <strVal> LEFTPARENTHESIS 		
%token <strVal> RIGHTPARENTHESIS 		
%token <strVal> SEMICOLON 				
%token <strVal> COMMA					
%token <strVal> COLON 					
%token <strVal> DOUBLECOLON 			
%token <strVal> DOT 					
%token <strVal> DOUBLEDOT 				

%type <strVal> funcname 

%type <symbolNode> funcprefix 

%type <forrNode> forprefix;

%type <callsuNode> callsuffix normcall methodcall

%type <symbolNode> funcdef
%type <exprNode> const
%type <exprNode> primary
%type <exprNode> term
%type <exprNode> assignexpr
%type <exprNode> expr

%type <exprNode> objectdef

%token COMMENT1 COMMENT2				
%type <exprNode> lvalue member call

%type <intVal> ifprefix elseprefix whilestart whilesecond

%type <intVal> M N

%right ASSIGN
%left	OR
%left   AND
%nonassoc EQUALS DIFF
%nonassoc GREATER GREATEREQ LESS LESSEREQ
%left PLUS MINUS
%left MUL DIV MOD
%right NOT PLUSPLUS MINUSMINUS MINUS2
%left DOT DOUBLEDOT
%left LEFTBRACKET RIGHTBRACKET
%left LEFTPARENTHESIS RIGHTPARENTHESIS

%%

program	:	stmt program { printf("program->stmts;\n");}
			|  { printf("program->stmt\n");}
 
stmt :		expr SEMICOLON			{printf("stmt->expr;\n");}
			| ifstmt  				{printf("stmt->ifstmt\n");}
			| whilestmt				{printf("stmt->whilestmt\n");}  
			| forstmt  				{printf("stmt->forstmt\n");}
			| returnstmt 			{printf("stmt->returnstmt\n");}
			| BREAK SEMICOLON 		{printf("stmt->break;\n");
				if(loopcounter!=0){
					push_last(&BreakStack, makeBreakStruct(nextquadlabel())); 
					emit(jump, NULL, NULL, NULL, yylineno);
				}else{
					yyerror("BREAK not in a loop");
				}
			}

			| CONTINUE SEMICOLON	{printf("stmt->continue;\n");
				if(loopcounter!=0){
					push_last(&ContinueStack, makeContinueStruct(nextquadlabel())); 
					emit(jump, NULL, NULL, NULL, yylineno);
				}else{
					yyerror("CONTINUE not in a loop");
				}
			}
			| block 				{printf("stmt->block;\n");}
			| funcdef 				{printf("stmt->fundef;\n");}
			| SEMICOLON 			{printf("stmt->;\n");};
 
expr : 		 assignexpr  {printf("expr -> assignexpr\n");$$=$1;}
			| expr OR expr {printf("expr->expr or expr\n"); $$=logbool(or, $1, $3);} 
			| expr AND expr {printf("expr->expr and expr\n"); $$=logbool(and, $1, $3);}    
			| expr PLUS expr {	printf("expr->expr + expr\n");
							 	$$ = arithmetic(add, $1, $3);
							 }   
			| expr MINUS expr  {printf("expr->expr - expr\n");
							 	$$ = arithmetic(sub, $1, $3);
							 } 
			| expr MUL expr   {printf("expr->expr * expr\n");
							 	$$ = arithmetic(mul, $1, $3);
							 } 
			| expr DIV expr   {printf("expr->expr / expr\n");
							 	$$ = arithmetic(diV, $1, $3);
							 } 
			| expr MOD expr   {printf("expr->expr mod expr\n");
							 	$$ = arithmetic(mod, $1, $3);
							 } 
			| expr EQUALS expr  {printf("expr->expr == expr\n");$$=relbool(if_eq, $1, $3);} 
			| expr DIFF expr   {printf("expr->expr != expr\n");$$=relbool(if_noteq, $1, $3);}
			| expr GREATER expr   {printf("expr->expr > expr\n");$$=relbool(if_greater, $1, $3);}
			| expr GREATEREQ expr   {printf("expr->expr >= expr\n");$$=relbool(if_greatereq, $1, $3);}
			| expr LESSEREQ expr   {printf("expr->expr <= expr\n");$$=relbool(if_lesseq, $1, $3);}
			| expr LESS expr   {printf("expr->expr < expr\n");$$=relbool(if_less, $1, $3);}
			| term {printf("expr->term\n"); $$=$1;} ;
	

term : 		LEFTPARENTHESIS expr RIGHTPARENTHESIS {printf("term-> ( expr )\n");$$=$2;}   
			| MINUS expr %prec MINUS2 
			{
				checkuminus($2);
				$$=newexpr(arithexpr_e);
				$$->sym=istempexpr($2)?$2->sym:newtemp();
				emit(uminus,$2, NULL, $$, yylineno);
				printf("term->- expr\n");
			}
			| NOT expr {
				
				$$=newexpr(boolexpr_e);
				$$->sym=newtemp();
				emit(not,$2,NULL,$$,yylineno);

				printf("term-> not expr\n");
			}
 		 	| PLUSPLUS lvalue {
 		 		if( $2 != NULL ){
						if ($2->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ($2->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

				if ($2->type==tableitem_e){
					$$=emit_iftableitem($2);
					emit(add,$$,newexpr_constnum(1),$$,yylineno);
					emit(tablesetelem,$2,$2->index,$$,yylineno);
				}
				else{
					emit(add,$2,newexpr_constnum(1),$2,yylineno);
					$$=newexpr(arithexpr_e);
					$$->sym=newtemp();
					emit(assign,$2,NULL,$$,yylineno);
				}


 		 		printf("term->++lvalue\n");}   
 		 	| lvalue PLUSPLUS  {

 		 		if( $1 != NULL ){
						if ($1->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ($1->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

				$$=newexpr(var_e);
				$$->sym=newtemp();

				if ($1->type==tableitem_e) {
					
					$1=emit_iftableitem($1);
					emit(assign,$1,NULL, $$, yylineno);
					emit(add,$1,newexpr_constnum(1),$1,yylineno);
					emit(tablesetelem,$1,$1->index,$1,yylineno);
				}
				else{

					emit(assign,$1,NULL,$$,yylineno);
					emit(add,$1,newexpr_constnum(1),$1,yylineno);
				}	

 		 		printf("term-> lvalue++\n");}
 		 	| MINUSMINUS lvalue  {

 		 		if( $2 != NULL ){
						if ($2->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ($2->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

				if ($2->type==tableitem_e){
					$$=emit_iftableitem($2);
					emit(add,$$,newexpr_constnum(1),$$,yylineno);
					emit(tablesetelem,$2,$2->index,$$,yylineno);
				}
				else{
					emit(sub,$2,newexpr_constnum(1),$2,yylineno);
					$$=newexpr(arithexpr_e);
					$$->sym=newtemp();
					emit(assign,$2,NULL,$$,yylineno);
				}

 		 		printf("term-> --lvalue\n");} 
 		 	| lvalue MINUSMINUS {

 		 		if( $1 != NULL ){
						if ($1->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ($1->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

				$$=newexpr(var_e);
				$$->sym=newtemp();


				if ($1->type==tableitem_e) {
					
					$1=emit_iftableitem($1);
					emit(assign,$1,NULL, $$, yylineno);
					emit(add,$1,newexpr_constnum(1),$1,yylineno);
					emit(tablesetelem,$1,$1->index,$1,yylineno);
				}
				else{

					emit(assign,$1,NULL,$$,yylineno);
					emit(sub,$1,newexpr_constnum(1),$1,yylineno);
				}	

 		 		printf("term-> lvalue--\n");}
 		 	| primary {printf("term-> primary\n"); $$=$1;};

assignexpr : lvalue ASSIGN expr {


					if( $1 != NULL ){
						if ($1->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ($1->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

					printf("assginexpr -> lvalue = expr\n");

					if($1->type == tableitem_e){
						emit(tablesetelem, $1, $1->index, $3, yylineno);
						$$ = emit_iftableitem($1);
						$$->type = assignexpr_e;
					}else{
						emit(assign, $3, (expr*)0, $1, yylineno);
						$$ = newexpr(assignexpr_e);
						$$->sym = newtemp();
						emit(assign, $1, (expr*)0, $$,yylineno);
					}														

			};

 
primary :	lvalue  {printf("primary->lvalue\n"); $$=emit_iftableitem($1);} 
			| call    {printf("primary->call\n");} 
			| objectdef    {printf("primary->objecrdef\n");} 
			| LEFTPARENTHESIS funcdef RIGHTPARENTHESIS    
			{
				$$=newexpr(programfunc_e);
				$$->sym=$2;

				printf("primary->(funcdef)\n");

			} 
			| const  {printf("primary->const\n");} ;

lvalue : 	IDENT    {

					SymbolTableEntry  *tmp ;

					int scope1 = scope;

					while(scope1>=0 && (tmp=lookupScope(yytext,scope1)) == NULL){
						scope1--;
					}

					if(tmp!=NULL){
						$$ = lvalue_expr(tmp);
						//anaferome ekei
					}else if(scope ==0){
						insert(yytext,var_s, currscopespace(), currscopeoffset() );
						inccurrscopeoffset();
						$$ = lvalue_expr(lookupScope(yytext,0));
					}else{
						insert(yytext,var_s, currscopespace(), currscopeoffset() );
						inccurrscopeoffset();
						$$ = lvalue_expr(lookupScope(yytext,scope));
					}


				printf("lvalue->id\n");} 
			| LOCAL IDENT  {
					
					SymbolTableEntry  *tmp = lookupScope(yytext, scope);

					if(tmp == NULL){//den vriskw kati sto trexon scope

						//elegxos gia library
						int r  = isLibrary(yytext);
						if(r == 1){
							yyerror("trying to shadow libfunc");
						}else if(scope ==0){
							insert(yytext,var_s, currscopespace(), currscopeoffset() );
							inccurrscopeoffset();
						}else{
							insert(yytext,var_s, currscopespace(), currscopeoffset() );
							inccurrscopeoffset();
						}
						$$ = lvalue_expr(lookupScope(yytext, scope));

					}else{
						$$ = lvalue_expr(tmp);
						//vrikame metavliti i synartisi kai anaferomaste ekei
					}

							printf("lvalue->local id\n");}    
			| DOUBLECOLON IDENT  {


					SymbolTableEntry  *tmp = lookupScope(yytext, 0);

					if(tmp==NULL){
						yyerror("global variable not found");
					}else{
						//ANAFEROMASTE EKEI
						$$ = lvalue_expr(tmp);
					}



					printf("lvalue->::id\n");}    
			| member  {printf("lvalue->member\n"); $$=$1;} ;
 
member : 	lvalue DOT IDENT  {
				$$=member_item($1,$3);
				printf("member->lvalue . id\n");
			}
			| lvalue LEFTBRACKET expr RIGHTBRACKET {
				$1 = emit_iftableitem($1);
				$$ = newexpr(tableitem_e);
				$$->sym = $1->sym;
				$$->index=$3;
				printf("member->lvalue  [expr] \n");
			}   
			| call DOT IDENT  {
				$$=member_item($1,$3);
				printf("member->call . id\n");
			}
			| call LEFTBRACKET expr RIGHTBRACKET {
				$1 = emit_iftableitem($1);
				$$ = newexpr(tableitem_e);
				$$->sym = $1->sym;
				$$->index=$3;
				printf("member-> call  [expr] \n");
			}; 
 
call  :		call LEFTPARENTHESIS elist RIGHTPARENTHESIS   {
				printf("call->call ( elist )\n");
				$$ = make_call($1, NULL);
			}
			| lvalue callsuffix   {
				printf("call-> lvalue callsuffix\n");
				if ($2->method){
					expr* self = $1;
					$1 = emit_iftableitem(member_item(self, $2->name));
					
					//$2.elist.add_front(self);
					struct Element * el = makeElistStruct(self);
					if(ElistStack.head == NULL){
						ElistStack.head = ElistStack.tail = el;
					}else{
						ElistStack.tail->next = el;
						ElistStack.tail = el;
					}
					ElistStack.count++;
				}
				$$ = make_call($1, NULL);
			}
			| LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS {
				printf("call->( funcdef) ( elist )\n");
				expr* func = newexpr(programfunc_e);
				func->sym =$2;
				$$ = make_call(func, NULL);
			};
 
callsuffix:	normcall  {printf("callsuffix -> normcall\n"); $$ = $1;}
			|  methodcall {printf("callsuffix -> methodcall\n"); $$ = $1;};

normcall :	LEFTPARENTHESIS elist RIGHTPARENTHESIS {
					printf("normcall -> ( elist )\n");
					
					//$methodcall.elist = $4;

					$$ = (struct callsu*)calloc(1, sizeof(struct callsu));
					$$->method = false;
					$$->name = NULL;
			};

methodcall :	DOUBLEDOT IDENT LEFTPARENTHESIS elist RIGHTPARENTHESIS {
					printf("methodcall ->.. id ( elist )\n");
					//$methodcall.elist = $4;
					$$ = (struct callsu*)calloc(1, sizeof(struct callsu));
					$$->method = true;
					$$->name = $2;
				}

save_elist : expr { push_first(&ElistStack, makeElistStruct($1)); }

more_elist  :  COMMA save_elist more_elist {}
			| {};
	
elist	: save_elist more_elist {printf("[ expr [, expr] * ]\n");} 
		| {};


objectdef :	LEFTBRACKET elist RIGHTBRACKET {printf("objectdef ->[ elist ]\n");

			expr * t = newexpr(newtable_e);
			
			t->sym = newtemp();
			emit(tablecreate,t,NULL,NULL,yylineno);
			int i;
			expr * x;
			for(i=ElistStack.count;(x = getElist(pop(&ElistStack)))!=NULL;i--){
				emit(tablesetelem,t,newexpr_constnum(i-1),x, yylineno);
			}

			$$=t;



			}
			| LEFTBRACKET indexed RIGHTBRACKET {printf("objectdef -> [ indexed ]\n");
							expr* t = newexpr(newtable_e);
													t->sym = newtemp();
													emit(tablecreate, t, NULL, NULL, yylineno);

													struct IndexedStruct * e = (struct IndexedStruct *)pop(&IndexedStack);
													
													while(e!=NULL){
														expr *x = e->k1;
														expr *y = e->k2;
														emit(tablesetelem, t, x, y, yylineno);
														e = (struct IndexedStruct *)pop(&IndexedStack);
													}

													/*
													for(x,y in $2){
														emit(tablesetelem, t, x, y);
													}*/
													$$ = t;
			};
													

more_indexed  : COMMA indexedelem more_indexed {}
		|  {}
		;
	
indexed	: indexedelem more_indexed {printf("[indexedelem [, indexedelem] * ]\n");

};

indexedelem :	LEFTBRACE expr COLON expr RIGHTBRACE {printf("indexedelem -> { expr : expr }\n");
push_last(&IndexedStack, makeIndexedStruct($2,$4));};

blockstmt:	blockstmt stmt	{}
			|{};
 
block :  LEFTBRACE {scope++;}  blockstmt RIGHTBRACE {hide(scope);scope--;}{printf(" stmt*\n");};

funcblockstart: {push_last(&loopcounterStack, makeLoopcounterStruct(loopcounter)); loopcounter=0; }

funcblockend: { loopcounter = getLoopcounter(pop(&loopcounterStack)); }

fblock : funcblockstart LEFTBRACE blockstmt RIGHTBRACE {hide(scope);scope--;} funcblockend

funcname: IDENT {
	
		if(isLibrary(yytext)==1){
			yyerror("func shadows libfunc");
		}else{
			SymbolTableEntry  *tmp = lookupScope(yytext,scope);
			if(tmp!=NULL){
				if(tmp->type==programfunc_s){
					yyerror("function redeclared");
				}
				else{
					yyerror("variable redeclared");
				}
			}else{
				insert(yytext,programfunc_s, currscopespace(), currscopeoffset() );
				//inccurrscopeoffset();
				$$ = strdup(yytext);
			}
		}
} | {
	
		static int functioncounter = 0;
		char *func = malloc(10);
		sprintf(func, "%s%d", "_f", functioncounter++);
		$$ = func;
		insert(func,programfunc_s, currscopespace(), currscopeoffset() );
		//inccurrscopeoffset();
};


funcprefix: FUNCTION funcname
{
	$$=lookupScope($2, scope);
	$$->iaddress=nextquadlabel();
	emit(funcstart,NULL,NULL,lvalue_expr($$), yylineno);
	
	push_last(&functionLocalsStack, makeFunctionLocalOffsetStruct(functionLocalOffset));
	enterscopespace();
	resetformalargsoffset();
};

funcargs: LEFTPARENTHESIS {scope++;} idlist RIGHTPARENTHESIS
{
	enterscopespace();
	resetfunctionlocaloffset();
};

funcbody: fblock
{
	exitscopespace();	
};

funcdef: funcprefix funcargs funcbody
{
	exitscopespace();
	$1->totallocals=functionLocalOffset;
	
	functionLocalOffset = getFunctionLocalOffset(pop(&functionLocalsStack));
	
	$$=$1;

	emit(funcend,NULL,NULL,lvalue_expr($1), yylineno);
	printf("function id (idlist) block\n");
};
 
const : 	INTCONST {printf("const->number\n");$$=newexpr_constnum($1);}
			| REALCONST {printf("const->number\n");$$=newexpr_constnum($1);}
			| STRING {printf("const->string\n");$$=newexpr_conststring($1);}
			| NIL {printf("const->nil\n");$$=newexpr(nil_e);}
			| TRUE {printf("const->true\n");$$=newexpr_constbool(true);}
			| FALSE {printf("cost->false\n");$$=newexpr_constbool(false);};

more_idlist  :  COMMA IDENT {
					SymbolTableEntry  *tmp=lookupScope(yytext,scope);
				if(tmp!=NULL){
					yyerror("formal redeclared");
				}
				else if(isLibrary(yytext)==1){
					yyerror("formal shadows libfunc");
				}
				else{
					insert(yytext,var_s, currscopespace(), currscopeoffset() );
					inccurrscopeoffset();
				}
				} more_idlist {}
			| {};
	
idlist	: IDENT
			{
				SymbolTableEntry  *tmp=lookupScope(yytext,scope);
				if(tmp!=NULL){
					yyerror("formal redeclared");
				}
				else if(isLibrary(yytext)==1){
					yyerror("formal shadows libfunc");
				}
				else{
					insert(yytext,var_s, currscopespace(), currscopeoffset() );
					inccurrscopeoffset();
				}
			}

				 more_idlist {printf("\n");} 
		| {};


ifprefix: 	IF LEFTPARENTHESIS expr RIGHTPARENTHESIS{
				emit_label(if_eq, $3, newexpr_constbool(1),NULL, nextquadlabel()+2, yylineno);
				$$ = nextquadlabel();
				emit(jump, NULL, NULL, NULL, yylineno);
			}

elseprefix: ELSE{
				$$ = nextquadlabel();
				emit(jump, NULL, NULL, NULL, yylineno);
			}

ifstmt: 	ifprefix stmt elseprefix stmt{
				patchlabel($1,$3+1);
				patchlabel($3, nextquadlabel());}
			| ifprefix stmt{
				patchlabel($1, nextquadlabel());
			}

loopend: 	{loopcounter--;}
loopstart: 	{loopcounter++; ElistStack.head = ElistStack.tail = NULL; ElistStack.count = 0;}

loopstmt: 	loopstart stmt loopend { /*$$ = $2;*/ }

whilestart:		WHILE{
						$$ = nextquadlabel();
				}

whilesecond:	LEFTPARENTHESIS expr RIGHTPARENTHESIS{
					emit_label(if_eq, $2, newexpr_constbool(1), NULL,nextquadlabel()+2, yylineno);
					$$ = nextquadlabel();
					emit(jump, NULL, NULL, NULL, yylineno);
													 }

whilestmt:		whilestart whilesecond loopstmt{
					emit_label(jump, NULL, NULL, NULL, $1, yylineno);
					patchlabel($2, nextquadlabel());
					
					
																
																//patchlabel(stmt.contlist, $2+1);		
																void *elem = top(&ContinueStack);
																int i,l;
																while(elem != NULL){
																	l = getContinueL(elem);
																	if(l == (loopcounter+1)){
																		i = getContinueI(elem);
																		patchlabel(i, $1);
																		pop(&ContinueStack);
																	}
																	else{
																		break;
																	}
																	elem = top(&ContinueStack);
																}

																elem = top(&BreakStack);

																//patchlabel(stmt.breaklist, nextquadlabel());
																while(elem != NULL){
																	l = getBreakL(elem);
																	if(l == (loopcounter+1)){
																		i = getBreakI(elem);
																		patchlabel(i, nextquadlabel());
																		pop(&BreakStack);
																	}
																	else{
																		break;
																	}
																	elem = top(&BreakStack);
																}
				}

N:				{
					$$ = nextquadlabel();
					emit(jump, NULL, NULL, NULL, yylineno);
				}

M:				{
					$$ = nextquadlabel();
				}

forprefix:		FOR LEFTPARENTHESIS elist SEMICOLON M expr SEMICOLON{
																		$$ = calloc(1, sizeof(struct forr));
																		$$->test = $5;
																		$$->enter = nextquadlabel();
																		emit(if_eq, $6, newexpr_constbool(1), NULL, yylineno);
																    } 

forstmt: 		forprefix N	elist RIGHTPARENTHESIS N loopstmt N{
																patchlabel($1->enter, $5+1);
																patchlabel($2, nextquadlabel());
																patchlabel($5, $1->test);
																patchlabel($7, $2+1);

																int i;
																int l;


																void * elem = top(&ContinueStack);

																//patchlabel(stmt.contlist, $2+1);
																while(elem != NULL){
																	l = getContinueL(elem);
																	if(l == (loopcounter+1)){
																		i = getContinueI(elem);
																		patchlabel(i, $2+1);
																		pop(&ContinueStack);
																	}
																	else{
																		break;
																	}
																	elem = top(&ContinueStack);
																}

																elem = top(&BreakStack);

																//patchlabel(stmt.breaklist, nextquadlabel());
																while(elem != NULL){
																	l = getBreakL(elem);
																	if(l == (loopcounter+1)){
																		i = getBreakI(elem);
																		patchlabel(i, nextquadlabel());
																		pop(&BreakStack);
																	}
																	else{
																		break;
																	}
																	elem = top(&BreakStack);
																}
																
															}

returnstmt: RETURN  expr SEMICOLON {
				if(functionlocal == currscopespace())
					emit(ret,$2,NULL,NULL,yylineno);
				else
					yyerror("RETURN not in a function");

				printf("returnstmt -> return expr;\n");
			}
			|  RETURN SEMICOLON {
				if(functionlocal == currscopespace())
					emit(ret,NULL,NULL,NULL,yylineno);
				else
					yyerror("RETURN not in a function");
				printf("returnstmt -> return ;\n");
			}
			;

%%


int main(int argc, char *argv[]){
	
	if(argc > 1){
		if(!(yyin = fopen(argv[1],"r"))){
			fprintf(stderr, "Cannot read the file:%s\n",argv[1]);
			return 0;
		}
	}else{
		yyin = stdin;
	}


	if(argc > 2){
		if(!(yyin = fopen(argv[2],"w"))){
			fprintf(stderr, "Cannot write the file:%s\n", argv[2]);
			return 0;
		}
	}else{
		yyout = stdout;
	}

	addLibrary("print");
	addLibrary("objectmemberkeys");
	addLibrary("objecttotalmembers");
	addLibrary("objectcopy");
	addLibrary("totalarguments");
	addLibrary("argument");
	addLibrary("typeof");
	addLibrary("strtonum");
	addLibrary("sqrt");
	addLibrary("cos");
	addLibrary("sin");
	addLibrary("input");

	initLists();

	yyparse();
	
	printfHashTable();
	
	printICODE();

	generate ();

	void *elem = top(&IncompleteStructStack);
	int instNo, iaddress;
	while(elem != NULL){
		instNo = getIncompleteX(elem);
		iaddress = getIncompleteY(elem);

		if(iaddress == currQuad){
			instructions[instNo].result->val = currInstruction;
		}else{
			instructions[instNo].result->val = quads[iaddress].taddress;
		}


		elem = pop(&IncompleteStructStack);
	}

	printFCODE();


	//write binary file
	FILE *file = fopen("mpekas.abc", "wb+");
	int i;
	//grafoume to magic number
	unsigned int magic = 340200501;
	fwrite(&magic, sizeof(unsigned int), 1, file);

	//grafw posa strings exoume
	unsigned int total = totalStringConsts;
	fwrite(&total, sizeof(unsigned int), 1, file);

	//gia kathe ena string
	for(i=0;i<total;++i){
		//grafoume posous xaraktires exei
		unsigned int total1 = strlen(stringConsts[i]);
		fwrite(&total1, sizeof(unsigned int), 1, file);

		//kai tous xaraktires
		fwrite(stringConsts[i], sizeof(char), total1, file);
	}

	//grafw posa numbers exoume
	total = totalNumCosts;
	fwrite(&total, sizeof(unsigned int), 1, file);

	//gia kathe ena number
	for(i=0;i<total;++i){
		//grafoume to number
		//total = strlen(stringConsts[i]);
		fwrite(&numCosts[i], sizeof(double), 1, file);
	}


	//grafw posa userfuncs exoume
	total = totalUserFuncs;
	fwrite(&total, sizeof(unsigned int), 1, file);

	//gia kathe ena number
	for(i=0;i<total;++i){
		//grafoume to userfunc
		//total = strlen(stringConsts[i]);
		fwrite(&userFuncs[i].address, sizeof(unsigned int), 1, file);
		fwrite(&userFuncs[i].localSize, sizeof(unsigned int), 1, file);
	
		//grafoume posous xaraktires exei
		unsigned int total1 = strlen(userFuncs[i].id);
		fwrite(&total1, sizeof(unsigned int), 1, file);

		//kai tous xaraktires
		fwrite(userFuncs[i].id, sizeof(char), total1, file);
	}


	//grafw posa strings exoume
	total = totalNamedLibFuncs;
	fwrite(&total, sizeof(unsigned int), 1, file);

	//gia kathe ena libfunc
	for(i=0;i<total;++i){
		//grafoume posous xaraktires exei
		unsigned int total1 = strlen(namedLibFuncs[i]);
		fwrite(&total1, sizeof(unsigned int), 1, file);

		//kai tous xaraktires
		fwrite(namedLibFuncs[i], sizeof(char), total1, file);
	}


	//grafw posa instructions exoume
	total = currInstruction;
	fwrite(&total, sizeof(unsigned int), 1, file);

	//gia kathe ena instruction
	for(i=0;i<total;++i){
		
		unsigned int total1;

		total1 = instructions[i].opcode;
		fwrite(&total1, sizeof(unsigned int), 1, file);


		//fprintf(stderr, "\n%d\n", total1);
		if(instructions[i].arg1){
			total1 = 1;
			fwrite(&total1, sizeof(unsigned int), 1, file);

			/*
			total1 = instructions[i].arg1->type;
			fwrite(&total1, sizeof(unsigned int), 1, file);

			total1 = instructions[i].arg1->val;
			fwrite(&total1, sizeof(unsigned int), 1, file);
			*/

			fwrite(&instructions[i].arg1->type, sizeof(instructions[i].arg1->type), 1, file);
			fwrite(&instructions[i].arg1->val, sizeof(instructions[i].arg1->val), 1, file);

		}else{
			total1 = 0;
			fwrite(&total1, sizeof(unsigned int), 1, file);
		}

		if(instructions[i].arg2){
			total1 = 1;
			fwrite(&total1, sizeof(unsigned int), 1, file);

			/*
			total1 = instructions[i].arg2->type;
			fwrite(&total1, sizeof(unsigned int), 1, file);

			total1 = instructions[i].arg2->val;
			fwrite(&total1, sizeof(unsigned int), 1, file);
*/
			fwrite(&instructions[i].arg2->type, sizeof(instructions[i].arg2->type), 1, file);
			fwrite(&instructions[i].arg2->val, sizeof(instructions[i].arg2->val), 1, file);
		}else{
			total1 = 0;
			fwrite(&total1, sizeof(unsigned int), 1, file);
		}

		if(instructions[i].result){
			total1 = 1;
			fwrite(&total1, sizeof(unsigned int), 1, file);
/*
			total1 = instructions[i].result->type;
			fwrite(&total1, sizeof(unsigned int), 1, file);

			total1 = instructions[i].result->val;
			fwrite(&total1, sizeof(unsigned int), 1, file);
*/
			fwrite(&instructions[i].result->type, sizeof(instructions[i].result->type), 1, file);
			fwrite(&instructions[i].result->val, sizeof(instructions[i].result->val), 1, file);
		}else{
			total1 = 0;
			fwrite(&total1, sizeof(unsigned int), 1, file);
		}


		
	}


	fwrite(&programVarOffset, sizeof(programVarOffset), 1, file);

	fclose(file);
 	//////////////////////////////////////////
}

//kwdikas deyteri fasi


int yyerror(char* yaccProvidedMessage){

	fprintf(stderr, "%s: at line %d, before token: %s\n", yaccProvidedMessage, yylineno, yytext);
	fprintf(stderr, "INPUT NOT VALID\n");

	exit(1);
	return -1;
}

int isLibrary(const char *a){
	
	if(strcmp(a, "print")==0) return 1;
	if(strcmp(a, "objectmemberkeys")==0) return 1;
	if(strcmp(a, "objecttotalmembers")==0) return 1;
	if(strcmp(a, "objectcopy")==0) return 1;
	if(strcmp(a, "totalarguments")==0) return 1;
	if(strcmp(a, "argument")==0) return 1;
	if(strcmp(a, "typeof")==0) return 1;
	if(strcmp(a, "strtonum")==0) return 1;
	if(strcmp(a, "sqrt")==0) return 1;
	if(strcmp(a, "cos")==0) return 1;
	if(strcmp(a, "sin")==0) return 1;
	
	return 0;
}

void addLibrary(const char *a){
	insert(a,libraryfunc_s, currscopespace(), currscopeoffset() );
	//inccurrscopeoffset();
}

unsigned int SymTable_hash(const char *pcKey)
{
  size_t ui;
  unsigned long uiHash = 0U;
  for (ui = 0U; pcKey[ui] != '\0'; ui++)
    uiHash = uiHash +  pcKey[ui];
  return uiHash % LEVELS;
}

//void insert(const char *name,int mode,enum SymbolTableType type){
void insert(const char *name, symbol_t type, scopespace_t space, unsigned offset){
		SymbolTableEntry *x = malloc(sizeof (SymbolTableEntry));
		x->isActive=true;
		//x->type=type;
		//if(mode==1){

		/*	x->value.varVal=malloc(sizeof (Variable));
			x->value.varVal->name=strdup(name);
			x->value.varVal->scope=scope;
			x->value.varVal->line=yylineno;

		}else if(mode==2){
*/
			//x->value.funcVal=malloc(sizeof (Function));
		
		x->name=strdup(name);
		x->scope=scope;
		x->line=yylineno;
		x->type=type;
		x->space=space;
		x->offset=offset;

//		}
		unsigned int b = SymTable_hash(name);
		if(BUCKETS[b]==NULL){
			BUCKETS[b]=x;
			BUCKETS[b]->nextC=NULL;
		}else{
				x->nextC=BUCKETS[b];
				BUCKETS[b]=x;
		}

		if(SCOPELISTS[scope]==NULL){
			SCOPELISTS[scope]=x;
			SCOPELISTS[scope]->nextS=NULL;
		}else{
			x->nextS=SCOPELISTS[scope];
			SCOPELISTS[scope]=x;
		}
	}

	void insert2(SymbolTableEntry *x){
		unsigned int b = SymTable_hash(x->name);
		if(BUCKETS[b]==NULL){
			BUCKETS[b]=x;
			BUCKETS[b]->nextC=NULL;
		}else{
				x->nextC=BUCKETS[b];
				BUCKETS[b]=x;
		}

		if(SCOPELISTS[scope]==NULL){
			SCOPELISTS[scope]=x;
			SCOPELISTS[scope]->nextS=NULL;
		}else{
			x->nextS=SCOPELISTS[scope];
			SCOPELISTS[scope]=x;
		}
	}

	SymbolTableEntry* lookupScope(char* name, int scope){
		unsigned int b=SymTable_hash(name);
		SymbolTableEntry* tmp = BUCKETS[b];
		while(tmp != NULL){

			if (strcmp(tmp->name, name)==0 && tmp->scope == scope && tmp->isActive == 1) {
					return tmp;
				}

				/*
			if (tmp->type == USERFUNC || tmp->type ==LIBFUNC ){
				if (strcmp(tmp->value.funcVal->name, name)==0 && tmp->value.funcVal->scope == scope && tmp->isActive == 1) {
					return tmp;
				}
			}else if (tmp->type == GLOBAL || tmp->type == LOCALL || tmp->type == FORMAL){
				if (strcmp(tmp->value.varVal->name, name)==0 && tmp->value.varVal->scope == scope && tmp->isActive == 1) {
					return tmp;
				}
			
			}*/
			tmp = tmp->nextC;
		}
		return NULL;
	}


	void hide(int scope){
		SymbolTableEntry* tmp = SCOPELISTS[scope];
		while(tmp != NULL){
			tmp->isActive=0;
			tmp = tmp->nextS;
		}
	}


	void printfHashTable(){

		int i;


		for(i=0;i<LEVELS;i++){
			if(SCOPELISTS[i] != NULL){
				printf("Symbols in scope #%d\n", i);

				SymbolTableEntry *ste = SCOPELISTS[i];
				while(ste !=NULL){


					if(ste->type == libraryfunc_s)
						printf("-> %s, (LIBFUNC) (Line %d)", ste->name, ste->line);
					if(ste->type == programfunc_s)
						printf("-> %s, (USERFUNC) (Line %d)", ste->name, ste->line);
					if(ste->type == var_s && ste->space == functionlocal)
						printf("-> %s, (LOCAL) (Line %d)", ste->name, ste->line);
					if(ste->type == var_s && ste->space == formalarg)
						printf("-> %s, (FORMAL) (Line %d)", ste->name, ste->line);
					if(ste->type == var_s && ste->space == programvar )
						printf("-> %s, (GLOBAL) (Line %d)", ste->name, ste->line);


					printf("\n");
					ste = ste->nextS;
				}


				printf("\n");

			}
		}
} 

//kwdikas triti fasi

scopespace_t currscopespace(void){
	if(scopeSpaceCounter==1)
	return programvar;
	else
	if(scopeSpaceCounter % 2==0)
		return formalarg;
	else 
		return functionlocal;
}

unsigned currscopeoffset(void){
	switch(currscopespace()){
		case programvar : return programVarOffset;
		case functionlocal : return functionLocalOffset;
		case formalarg : return formalArgOffset;
		default:assert(0);
	}
}


void inccurrscopeoffset (void){
	switch(currscopespace()){
		case programvar : ++programVarOffset; break;
		case functionlocal : ++functionLocalOffset; break;
		case formalarg : ++formalArgOffset; break;
		default: assert(0);
	}

}

void enterscopespace (void)
{
	++scopeSpaceCounter;
}

void exitscopespace(void){
	assert(scopeSpaceCounter>1); --scopeSpaceCounter;
}


void printICODE(){

	FILE *f = stderr;//fopen ("quads.txt", "w+");
	fprintf(f,"#quad\topcode\t\targ1\targ2\tresult\n--------------------------------------------\n");

	int i=0;
	for(;i<currQuad;i++){
		fprintf(f,"%d\t", i);
		switch(quads[i].op){
			case assign:
				fprintf(f,"assign\t");
				break;
			case add:
				fprintf(f,"add\t");
				break;
			case sub:
				fprintf(f,"sub\t");
				break;
			case mul:
				fprintf(f,"mul\t");
				break;
			case diV:
				fprintf(f,"div\t");
				break;
			case mod:
				fprintf(f,"mod\t");
				break;
			case uminus:
				fprintf(f,"uminus\t");
				break;
			case and:
				fprintf(f,"and\t");
				break;
			case or:
				fprintf(f,"or\t");
				break;
			case not:
				fprintf(f,"not\t");
				break;
			case if_eq:
				fprintf(f,"if_eq\t");
				break;
			case if_noteq:
				fprintf(f,"if_noteq");
				break;
			case if_lesseq:	
				fprintf(f,"if_lesseq");
				break;
			case if_greatereq:
				fprintf(f,"if_greatereq");
				break;
			case if_less:
				fprintf(f,"if_less\t");
				break;
			case if_greater:
				fprintf(f,"if_greater");
				break;
			case call:
				fprintf(f,"call\t");
				break;
			case param:
				fprintf(f,"param\t");
				break;
			case ret:
				fprintf(f,"ret\t");
				break;
			case getretval:
				fprintf(f,"getretval");
				break;
			case funcstart:
				fprintf(f,"funcstart");
				break;
			case funcend:
				fprintf(f,"funcend\t");
				break;
			case tablecreate:
				fprintf(f,"tablecreate");
				break;
			case tablegetelem:
				fprintf(f,"tablegetelem");
				break;
			case tablesetelem:
				fprintf(f,"tablesetelem");
				break;
			case jump:
				fprintf(f,"jump\t\t");
				break;
			default:
				break;
		}

		

		if(quads[i].arg1){
			if(quads[i].arg1->sym!=NULL){
	   			fprintf(f,"\t");
	   			fprintf(f,"%s", quads[i].arg1->sym->name);
	   		}else if(quads[i].arg1->sym ==NULL){
		 		fprintf(f,"\t");
		 		if(quads[i].arg1->type == conststring_e){
		 			fprintf(f,"\'%s\'", quads[i].arg1->strConst);
		 		}
		 		if(quads[i].arg1->type == constnum_e){
		 			fprintf(f,"%.3f", quads[i].arg1->numConst);
		 		}
		 		if(quads[i].arg1->type == constbool_e){
		 			fprintf(f,"%d", quads[i].arg1->boolConst);
		 			if(quads[i].arg1->boolConst == 1)
		 				fprintf(f,"(TRUE)");
		 			else
		 				fprintf(f,"(FALSE)");
		 		}
		 		if(quads[i].arg1->type == nil_e){
		 			fprintf(f,"NIL");
		 		}
		 	}
	 	}

	 	if(quads[i].arg2){
			if(quads[i].arg2->sym!=NULL){
	   			fprintf(f,"\t");
	   			fprintf(f,"%s", quads[i].arg2->sym->name);
	   		}else if(quads[i].arg2->sym ==NULL){
		 		fprintf(f,"\t");
		 		if(quads[i].arg2->type == conststring_e){
		 			fprintf(f,"\'%s\'", quads[i].arg2->strConst);
		 		}
		 		if(quads[i].arg2->type == constnum_e){
		 			fprintf(f,"%.3f", quads[i].arg2->numConst);
		 		}
		 		if(quads[i].arg2->type == constbool_e){
		 			fprintf(f,"%d", quads[i].arg2->boolConst);
		 			if(quads[i].arg2->boolConst == 1)
		 				fprintf(f,"(TRUE)");
		 			else
		 				fprintf(f,"(FALSE)");
		 		}
		 		if(quads[i].arg2->type == nil_e){
		 			fprintf(f,"NIL");
		 		}
	 		}
	 	}else{
	 		fprintf(f,"\t");
	 	}

	 	
		if(quads[i].result){
			if(quads[i].result->sym!=NULL){
	   			fprintf(f,"\t");
	   			fprintf(f,"%s", quads[i].result->sym->name);
	   		}else if(quads[i].result->sym ==NULL){
		 		fprintf(f,"\t");
		 		if(quads[i].result->type == conststring_e){
		 			fprintf(f,"\'%s\'", quads[i].result->strConst);
		 		}
		 		if(quads[i].result->type == constnum_e){
		 			fprintf(f,"%.3f", quads[i].result->numConst);
		 		}
		 		if(quads[i].result->type == constbool_e){
		 			fprintf(f,"%d", quads[i].result->boolConst);
		 			if(quads[i].result->boolConst == 1)
		 				fprintf(f,"(TRUE)");
		 			else
		 				fprintf(f,"(FALSE)");
		 		}
		 		if(quads[i].result->type == nil_e){
		 			fprintf(f,"NIL");
		 		}
		 	}
		 }else if(quads[i].op != ret && quads[i].op != call && quads[i].op != getretval
		 	&& quads[i].op != param && quads[i].op != tablecreate){
		 	fprintf(f,"\t");
		 	fprintf(f,"%d", quads[i].label);
		 }

	 	fprintf(f,"\n");

	}

	fclose(f);


}

void printFCODE(){

	FILE *f = stdout;//fopen ("quads.txt", "w+");
	int i=0;


	printf("\n#Arrays\n");
	printf("\nNumbers\n");

	for(i=0;i<totalNumCosts;i++){
		printf("[%d]: %5.3f\n", i, numCosts[i]);
	}

	printf("\nStrings\n");

	for(i=0;i<totalStringConsts;i++){
		printf("[%d]: %s\n", i, stringConsts[i]);
	}

	printf("\nLibrary Functions\n");

	for(i=0;i<totalNamedLibFuncs;i++){
		printf("[%d]: %s\n", i, namedLibFuncs[i]);
	}

	printf("\nUserFunctions\n");

	for(i=0;i<totalUserFuncs;i++){
		printf("[%d]: id=%s size=%d address=%d \n", i, userFuncs[i].id, userFuncs[i].localSize, userFuncs[i].address);
	}


	fprintf(f,"#instruction\tvmopcode\targ1\t\t\targ2\t\t\tresult\n");
	fprintf(f,"----------------------------------------------------------------------------------------\n");

	i=0;
	for(;i<currInstruction;i++){
		fprintf(f,"%d\t\t", i);
		switch(instructions[i].opcode){
			case assign_v:
				fprintf(f,"assign_v\t");
				break;
			case add_v:
				fprintf(f,"add_v\t\t");
				break;
			case sub_v:
				fprintf(f,"sub_v\t\t");
				break;
			case mul_v:
				fprintf(f,"mul_v\t\t");
				break;
			case div_v:
				fprintf(f,"div_v\t\t");
				break;
			case mod_v:
				fprintf(f,"mod_v\t\t");
				break;
			case uminus_v:
				fprintf(f,"uminus_v\t");
				break;
			case and_v:
				fprintf(f,"and_v\t");
				break;
			case or_v:
				fprintf(f,"or_v\t");
				break;
			case not_v:
				fprintf(f,"not_v\t");
				break;
			case jeq_v:
				fprintf(f,"jeq_v\t\t");
				break;
			case jne_v:
				fprintf(f,"jne_v\t\t");
				break;
			case jle_v:	
				fprintf(f,"jle_v\t\t");
				break;
			case jge_v:
				fprintf(f,"jge_v\t\t");
				break;
			case jlt_v:
				fprintf(f,"jlt_v\t\t");
				break;
			case jgt_v:
				fprintf(f,"jgt_v\t\t");
				break;
			case call_v:
				fprintf(f,"call_v\t");
				break;
			case pusharg_v:
				fprintf(f,"pusharg_v\t");
				break;
			//case ret:
			//	fprintf(f,"ret\t");
			//	break;
			//case getretval:
			//	fprintf(f,"getretval");
			//	break;
			case funcenter_v:
				fprintf(f,"funcenter_v");
				break;
			case funcexit_v:
				fprintf(f,"funcexit_v\t");
				break;
			case newtable_v:
				fprintf(f,"newtable_v");
				break;
			case tablegetelem_v:
				fprintf(f,"tablegetelem_v");
				break;
			case tablesetelem_v:
				fprintf(f,"tablesetelem_v");
				break;
			case jump_v:
				fprintf(f,"jump_v\t\t");
				break;
			case nop_v:
				fprintf(f,"nop_v\t\t");
				break;
			default:
				break;
		}

		if(instructions[i].arg1){
			printf("%d(", instructions[i].arg1->type);

			switch(instructions[i].arg1->type){
				case label_a:
					printf("label_a");
					break;
				case global_a:
					printf("global_a");
					break; 
				case formal_a:
					printf("formal_a");
					break;
				case local_a:
					printf("local_a");
					break;
				case number_a:
					printf("number_a");
					break;
				case string_a:
					printf("string_a");
					break;
				case bool_a:
					printf("bool_a");
					break;
				case nil_a:
					printf("nil_a");
					break;
				case userfunc_a:
					printf("userfunc_a");
					break;
				case libfunc_a:
					printf("libfunc_a");
					break;
				case retval_a:
					printf("retval_a");
					break;
				default:
					assert(0);
					break;
			}

			printf(")%d", instructions[i].arg1->val);
			
		}else{
			printf("\t");
		}

		if(instructions[i].arg2){
			printf("\t\t%d(", instructions[i].arg2->type);

			switch(instructions[i].arg2->type){
				case label_a:
					printf("label_a");
					break;
				case global_a:
					printf("global_a");
					break; 
				case formal_a:
					printf("formal_a");
					break;
				case local_a:
					printf("local_a");
					break;
				case number_a:
					printf("number_a");
					break;
				case string_a:
					printf("string_a");
					break;
				case bool_a:
					printf("bool_a");
					break;
				case nil_a:
					printf("nil_a");
					break;
				case userfunc_a:
					printf("userfunc_a");
					break;
				case libfunc_a:
					printf("libfunc_a");
					break;
				case retval_a:
					printf("retval_a");
					break;
				default:
					assert(0);
					break;
			}

			printf(")%d\t", instructions[i].arg2->val);
		}else{
			printf("\t\t\t\t");
		}

		if(instructions[i].result){
			printf("\t%d(", instructions[i].result->type);

			switch(instructions[i].result->type){
				case label_a:
					printf("label_a");
					break;
				case global_a:
					printf("global_a");
					break; 
				case formal_a:
					printf("formal_a");
					break;
				case local_a:
					printf("local_a");
					break;
				case number_a:
					printf("number_a");
					break;
				case string_a:
					printf("string_a");
					break;
				case bool_a:
					printf("bool_a");
					break;
				case nil_a:
					printf("nil_a");
					break;
				case userfunc_a:
					printf("userfunc_a");
					break;
				case libfunc_a:
					printf("libfunc_a");
					break;
				case retval_a:
					printf("retval_a");
					break;
				default:
					assert(0);
					break;
			}

			printf(")%d", instructions[i].result->val);
		}
					

		
/*
		if(quads[i].arg1){
			if(quads[i].arg1->sym!=NULL){
	   			fprintf(f,"\t");
	   			fprintf(f,"%s", quads[i].arg1->sym->name);
	   		}else if(quads[i].arg1->sym ==NULL){
		 		fprintf(f,"\t");
		 		if(quads[i].arg1->type == conststring_e){
		 			fprintf(f,"\'%s\'", quads[i].arg1->strConst);
		 		}
		 		if(quads[i].arg1->type == constnum_e){
		 			fprintf(f,"%.3f", quads[i].arg1->numConst);
		 		}
		 		if(quads[i].arg1->type == constbool_e){
		 			fprintf(f,"%d", quads[i].arg1->boolConst);
		 			if(quads[i].arg1->boolConst == 1)
		 				fprintf(f,"(TRUE)");
		 			else
		 				fprintf(f,"(FALSE)");
		 		}
		 		if(quads[i].arg1->type == nil_e){
		 			fprintf(f,"NIL");
		 		}
		 	}
	 	}

	 	if(quads[i].arg2){
			if(quads[i].arg2->sym!=NULL){
	   			fprintf(f,"\t");
	   			fprintf(f,"%s", quads[i].arg2->sym->name);
	   		}else if(quads[i].arg2->sym ==NULL){
		 		fprintf(f,"\t");
		 		if(quads[i].arg2->type == conststring_e){
		 			fprintf(f,"\'%s\'", quads[i].arg2->strConst);
		 		}
		 		if(quads[i].arg2->type == constnum_e){
		 			fprintf(f,"%.3f", quads[i].arg2->numConst);
		 		}
		 		if(quads[i].arg2->type == constbool_e){
		 			fprintf(f,"%d", quads[i].arg2->boolConst);
		 			if(quads[i].arg2->boolConst == 1)
		 				fprintf(f,"(TRUE)");
		 			else
		 				fprintf(f,"(FALSE)");
		 		}
		 		if(quads[i].arg2->type == nil_e){
		 			fprintf(f,"NIL");
		 		}
	 		}
	 	}else{
	 		fprintf(f,"\t");
	 	}

	 	
		if(quads[i].result){
			if(quads[i].result->sym!=NULL){
	   			fprintf(f,"\t");
	   			fprintf(f,"%s", quads[i].result->sym->name);
	   		}else if(quads[i].result->sym ==NULL){
		 		fprintf(f,"\t");
		 		if(quads[i].result->type == conststring_e){
		 			fprintf(f,"\'%s\'", quads[i].result->strConst);
		 		}
		 		if(quads[i].result->type == constnum_e){
		 			fprintf(f,"%.3f", quads[i].result->numConst);
		 		}
		 		if(quads[i].result->type == constbool_e){
		 			fprintf(f,"%d", quads[i].result->boolConst);
		 			if(quads[i].result->boolConst == 1)
		 				fprintf(f,"(TRUE)");
		 			else
		 				fprintf(f,"(FALSE)");
		 		}
		 		if(quads[i].result->type == nil_e){
		 			fprintf(f,"NIL");
		 		}
		 	}
		 }else if(quads[i].op != ret && quads[i].op != call && quads[i].op != getretval
		 	&& quads[i].op != param && quads[i].op != tablecreate){
		 	fprintf(f,"\t");
		 	fprintf(f,"%d", quads[i].label);
		 }
		 */

	 	fprintf(f,"\n");

	}

	fclose(f);


}

