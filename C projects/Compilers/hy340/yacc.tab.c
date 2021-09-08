/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yacc.y" /* yacc.c:339  */

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



#line 1366 "yacc.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc.tab.h".  */
#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTCONST = 258,
    REALCONST = 259,
    IDENT = 260,
    STRING = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOR = 265,
    FUNCTION = 266,
    RETURN = 267,
    BREAK = 268,
    CONTINUE = 269,
    AND = 270,
    NOT = 271,
    OR = 272,
    LOCAL = 273,
    TRUE = 274,
    FALSE = 275,
    NIL = 276,
    ASSIGN = 277,
    PLUS = 278,
    MINUS = 279,
    MUL = 280,
    DIV = 281,
    MOD = 282,
    EQUALS = 283,
    DIFF = 284,
    PLUSPLUS = 285,
    MINUSMINUS = 286,
    GREATER = 287,
    LESS = 288,
    GREATEREQ = 289,
    LESSEREQ = 290,
    LEFTBRACE = 291,
    RIGHTBRACE = 292,
    LEFTBRACKET = 293,
    RIGHTBRACKET = 294,
    LEFTPARENTHESIS = 295,
    RIGHTPARENTHESIS = 296,
    SEMICOLON = 297,
    COMMA = 298,
    COLON = 299,
    DOUBLECOLON = 300,
    DOT = 301,
    DOUBLEDOT = 302,
    COMMENT1 = 303,
    COMMENT2 = 304,
    MINUS2 = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 1303 "yacc.y" /* yacc.c:355  */


	int intVal;
	double realVal;
	char* strVal;
	struct expr* exprNode; 
	struct symbol* symbolNode;

	struct forr* forrNode;
	struct callsu* callsuNode;


#line 1470 "yacc.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 1485 "yacc.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   646

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  1402,  1402,  1403,  1405,  1406,  1407,  1408,  1409,  1410,
    1419,  1427,  1428,  1429,  1431,  1432,  1433,  1434,  1437,  1440,
    1443,  1446,  1449,  1450,  1451,  1452,  1453,  1454,  1455,  1458,
    1459,  1467,  1475,  1498,  1525,  1548,  1576,  1578,  1605,  1606,
    1607,  1608,  1616,  1618,  1643,  1668,  1683,  1685,  1689,  1696,
    1700,  1708,  1712,  1730,  1737,  1738,  1740,  1750,  1758,  1760,
    1761,  1763,  1764,  1767,  1784,  1806,  1807,  1810,  1814,  1817,
    1818,  1820,  1820,  1820,  1822,  1824,  1826,  1826,  1828,  1847,
    1858,  1869,  1869,  1875,  1880,  1893,  1894,  1895,  1896,  1897,
    1898,  1900,  1900,  1913,  1916,  1915,  1931,  1934,  1940,  1945,
    1948,  1952,  1953,  1955,  1957,  1961,  1967,  2006,  2011,  2015,
    2022,  2066,  2074
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTCONST", "REALCONST", "IDENT",
  "STRING", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK",
  "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE", "FALSE", "NIL",
  "ASSIGN", "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQUALS", "DIFF",
  "PLUSPLUS", "MINUSMINUS", "GREATER", "LESS", "GREATEREQ", "LESSEREQ",
  "LEFTBRACE", "RIGHTBRACE", "LEFTBRACKET", "RIGHTBRACKET",
  "LEFTPARENTHESIS", "RIGHTPARENTHESIS", "SEMICOLON", "COMMA", "COLON",
  "DOUBLECOLON", "DOT", "DOUBLEDOT", "COMMENT1", "COMMENT2", "MINUS2",
  "$accept", "program", "stmt", "expr", "term", "assignexpr", "primary",
  "lvalue", "member", "call", "callsuffix", "normcall", "methodcall",
  "save_elist", "more_elist", "elist", "objectdef", "more_indexed",
  "indexed", "indexedelem", "blockstmt", "block", "$@1", "$@2",
  "funcblockstart", "funcblockend", "fblock", "$@3", "funcname",
  "funcprefix", "funcargs", "$@4", "funcbody", "funcdef", "const",
  "more_idlist", "$@5", "idlist", "$@6", "ifprefix", "elseprefix",
  "ifstmt", "loopend", "loopstart", "loopstmt", "whilestart",
  "whilesecond", "whilestmt", "N", "M", "forprefix", "forstmt",
  "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF -168

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-168)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     216,  -168,  -168,  -168,  -168,   -22,  -168,   -12,    26,   259,
     -10,    -7,   335,    36,  -168,  -168,  -168,   335,    -2,    -2,
    -168,   289,   312,  -168,    39,    47,   216,   381,  -168,  -168,
    -168,   -17,  -168,     2,  -168,  -168,    -4,  -168,  -168,   216,
    -168,     9,  -168,  -168,  -168,  -168,   335,   335,  -168,  -168,
    -168,   402,  -168,  -168,  -168,  -168,  -168,    40,   -13,     2,
     -13,  -168,   335,   570,     7,    14,    21,    18,   444,    27,
    -168,  -168,  -168,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,  -168,   335,  -168,  -168,
     335,   335,    62,    64,  -168,  -168,  -168,   335,   335,    65,
    -168,  -168,    63,   335,  -168,   335,   465,    30,  -168,    48,
     123,   359,   335,  -168,  -168,  -168,    52,  -168,  -168,    51,
     598,   585,   -19,   -19,  -168,  -168,  -168,   611,   611,    31,
      31,    31,    31,   570,   507,    53,  -168,    55,   528,    57,
    -168,    87,    60,  -168,  -168,  -168,   216,   486,   216,  -168,
      58,  -168,  -168,    51,  -168,  -168,   335,     7,    18,   335,
    -168,  -168,   335,  -168,  -168,  -168,    59,  -168,  -168,  -168,
    -168,  -168,   335,  -168,   549,  -168,  -168,    61,    66,    50,
    -168,   173,  -168,  -168,   423,  -168,  -168,  -168,    96,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,    50,  -168,  -168
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    85,    86,    43,    87,     0,   104,     0,    79,     0,
       0,     0,     0,     0,    89,    90,    88,     0,     0,     0,
      71,    62,     0,    13,     0,     0,     3,     0,    28,    14,
      36,    38,    46,    39,    40,    11,     0,    12,    42,     0,
       5,     0,     6,   107,     7,     8,     0,    62,    78,    80,
     112,     0,     9,    10,    31,    44,    30,     0,    32,     0,
      34,    70,     0,    58,    60,     0,     0,    66,     0,     0,
      45,     1,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     4,     0,    33,    35,
       0,    62,     0,     0,    52,    54,    55,     0,    62,     0,
      81,    74,   100,     0,   102,    62,     0,     0,   111,     0,
       0,     0,     0,    61,    63,    64,     0,    67,    29,    41,
      16,    15,    17,    18,    19,    20,    21,    22,    23,    24,
      27,    25,    26,    37,     0,     0,    47,     0,     0,     0,
      49,    96,     0,    83,    84,    98,     0,     0,     0,   106,
       0,    97,   108,     0,    72,    69,     0,    60,    66,    62,
      48,    56,    62,    50,    51,    94,     0,    70,    99,   105,
     101,   107,     0,    73,     0,    59,    65,     0,     0,    93,
      82,     0,   103,   102,     0,    68,    53,    57,     0,    95,
      76,   107,   109,    91,    75,   110,    93,    77,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -168,    78,   -24,     0,  -168,  -168,  -168,    -8,  -168,     1,
    -168,  -168,  -168,    -6,   -52,   -46,  -168,   -50,  -168,    -5,
     -58,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,   -20,  -168,   -84,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,   -69,  -168,  -168,  -168,  -167,  -168,
    -168,  -168,  -168
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    63,    28,    29,    30,    31,    32,    33,
      94,    95,    96,    64,   113,    65,    34,   117,    66,    67,
     110,    35,    61,   173,   142,   197,   143,   194,    49,    36,
     101,   141,   144,    37,    38,   189,   196,   166,   179,    39,
     146,    40,   182,   148,   149,    41,   104,    42,   105,   172,
      43,    44,    45
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,   107,    69,     3,   183,    87,    77,    78,    79,    51,
      58,    60,    54,    88,    89,   102,    13,    56,    46,    59,
      59,    90,    68,    91,   195,    90,    27,    91,    47,    92,
      93,    48,    52,    92,    93,    53,   100,   109,    57,    27,
      97,    55,    98,    24,    70,   135,   106,    71,    99,   103,
     112,     8,   139,   114,    75,    76,    77,    78,    79,   150,
     115,   116,   111,    -1,    -1,    -1,    -1,   136,   119,   137,
     140,   145,   152,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   155,   133,    62,   153,
     134,   159,   165,   188,   161,   162,   167,   138,   164,   171,
     180,   193,   186,   147,    72,   175,   157,   187,   176,   181,
      27,   158,   198,   177,   191,     0,   178,     0,     0,     0,
       0,     0,   168,     0,   170,     0,     1,     2,     3,     4,
       5,     0,     6,     7,     8,     9,    10,    11,     0,    12,
       0,    13,    14,    15,    16,     0,    27,    17,    27,     0,
       0,     0,     0,    18,    19,     0,   174,   155,     0,    20,
     154,    21,     0,    22,     0,    23,     0,     0,    24,     0,
       0,     0,   184,     0,     0,     0,     1,     2,     3,     4,
       5,    27,     6,     7,     8,     9,    10,    11,     0,    12,
       0,    13,    14,    15,    16,     0,     0,    17,     0,     0,
       0,     0,     0,    18,    19,     0,     0,     0,     0,    20,
     190,    21,     0,    22,     0,    23,     0,     0,    24,     1,
       2,     3,     4,     5,     0,     6,     7,     8,     9,    10,
      11,     0,    12,     0,    13,    14,    15,    16,     0,     0,
      17,     0,     0,     0,     0,     0,    18,    19,     0,     0,
       0,     0,    20,     0,    21,     0,    22,     0,    23,     0,
       0,    24,     1,     2,     3,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,    13,    14,    15,
      16,     0,     0,    17,     0,     0,     0,     0,     0,    18,
      19,     0,     1,     2,     3,     4,     0,    21,     0,    22,
       0,    50,     0,     0,    24,    12,     0,    13,    14,    15,
      16,     0,     0,    17,     0,     1,     2,     3,     4,    18,
      19,     0,     0,     8,     0,    62,     0,    21,    12,    22,
      13,    14,    15,    16,    24,     0,    17,     0,     1,     2,
       3,     4,    18,    19,     0,     0,     0,     0,     0,     0,
      21,    12,    22,    13,    14,    15,    16,    24,     0,    17,
       0,     0,     0,     0,     0,    18,    19,     0,     0,     0,
       0,     0,     0,    21,    73,    22,    74,     0,     0,     0,
      24,     0,    75,    76,    77,    78,    79,    80,    81,     0,
       0,    82,    83,    84,    85,     0,    73,     0,    74,     0,
       0,     0,     0,   156,    75,    76,    77,    78,    79,    80,
      81,     0,     0,    82,    83,    84,    85,    73,     0,    74,
       0,     0,     0,    86,     0,    75,    76,    77,    78,    79,
      80,    81,     0,     0,    82,    83,    84,    85,    73,     0,
      74,     0,     0,     0,   108,     0,    75,    76,    77,    78,
      79,    80,    81,     0,     0,    82,    83,    84,    85,    73,
       0,    74,     0,     0,     0,   192,     0,    75,    76,    77,
      78,    79,    80,    81,     0,     0,    82,    83,    84,    85,
      73,     0,    74,     0,     0,   118,     0,     0,    75,    76,
      77,    78,    79,    80,    81,     0,     0,    82,    83,    84,
      85,    73,     0,    74,     0,     0,   151,     0,     0,    75,
      76,    77,    78,    79,    80,    81,     0,     0,    82,    83,
      84,    85,    73,     0,    74,     0,     0,   169,     0,     0,
      75,    76,    77,    78,    79,    80,    81,     0,     0,    82,
      83,    84,    85,    73,     0,    74,   160,     0,     0,     0,
       0,    75,    76,    77,    78,    79,    80,    81,     0,     0,
      82,    83,    84,    85,    73,     0,    74,   163,     0,     0,
       0,     0,    75,    76,    77,    78,    79,    80,    81,     0,
       0,    82,    83,    84,    85,    73,   185,    74,     0,     0,
       0,     0,     0,    75,    76,    77,    78,    79,    80,    81,
      73,     0,    82,    83,    84,    85,     0,     0,    75,    76,
      77,    78,    79,    80,    81,     0,     0,    82,    83,    84,
      85,    75,    76,    77,    78,    79,    80,    81,     0,     0,
      82,    83,    84,    85,    75,    76,    77,    78,    79,    -1,
      -1,     0,     0,    82,    83,    84,    85
};

static const yytype_int16 yycheck[] =
{
       0,    47,    22,     5,   171,    22,    25,    26,    27,     9,
      18,    19,    12,    30,    31,    39,    18,    17,    40,    18,
      19,    38,    22,    40,   191,    38,    26,    40,    40,    46,
      47,     5,    42,    46,    47,    42,    40,    57,    40,    39,
      38,     5,    40,    45,     5,    91,    46,     0,    46,    40,
      43,    11,    98,    39,    23,    24,    25,    26,    27,   105,
      39,    43,    62,    32,    33,    34,    35,     5,    41,     5,
       5,     8,    42,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,   110,    87,    36,    41,
      90,    40,     5,    43,    41,    40,    36,    97,    41,    41,
      41,     5,    41,   103,    26,   157,   112,    41,   158,   167,
     110,   116,   196,   159,   183,    -1,   162,    -1,    -1,    -1,
      -1,    -1,   146,    -1,   148,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    13,    14,    -1,    16,
      -1,    18,    19,    20,    21,    -1,   146,    24,   148,    -1,
      -1,    -1,    -1,    30,    31,    -1,   156,   181,    -1,    36,
      37,    38,    -1,    40,    -1,    42,    -1,    -1,    45,    -1,
      -1,    -1,   172,    -1,    -1,    -1,     3,     4,     5,     6,
       7,   181,     9,    10,    11,    12,    13,    14,    -1,    16,
      -1,    18,    19,    20,    21,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    36,
      37,    38,    -1,    40,    -1,    42,    -1,    -1,    45,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      14,    -1,    16,    -1,    18,    19,    20,    21,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,
      -1,    -1,    36,    -1,    38,    -1,    40,    -1,    42,    -1,
      -1,    45,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    -1,    18,    19,    20,
      21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,     3,     4,     5,     6,    -1,    38,    -1,    40,
      -1,    42,    -1,    -1,    45,    16,    -1,    18,    19,    20,
      21,    -1,    -1,    24,    -1,     3,     4,     5,     6,    30,
      31,    -1,    -1,    11,    -1,    36,    -1,    38,    16,    40,
      18,    19,    20,    21,    45,    -1,    24,    -1,     3,     4,
       5,     6,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    16,    40,    18,    19,    20,    21,    45,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    15,    40,    17,    -1,    -1,    -1,
      45,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    -1,    15,    -1,    17,    -1,
      -1,    -1,    -1,    44,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    15,    -1,    17,
      -1,    -1,    -1,    42,    -1,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    15,    -1,
      17,    -1,    -1,    -1,    42,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    15,
      -1,    17,    -1,    -1,    -1,    42,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      15,    -1,    17,    -1,    -1,    41,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    15,    -1,    17,    -1,    -1,    41,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,    15,    -1,    17,    -1,    -1,    41,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    15,    -1,    17,    39,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    15,    -1,    17,    39,    -1,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    15,    37,    17,    -1,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      15,    -1,    32,    33,    34,    35,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    14,    16,    18,    19,    20,    21,    24,    30,    31,
      36,    38,    40,    42,    45,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    67,    72,    80,    84,    85,    90,
      92,    96,    98,   101,   102,   103,    40,    40,     5,    79,
      42,    54,    42,    42,    54,     5,    54,    40,    58,    60,
      58,    73,    36,    54,    64,    66,    69,    70,    54,    84,
       5,     0,    52,    15,    17,    23,    24,    25,    26,    27,
      28,    29,    32,    33,    34,    35,    42,    22,    30,    31,
      38,    40,    46,    47,    61,    62,    63,    38,    40,    46,
      40,    81,    53,    40,    97,    99,    54,    66,    42,    84,
      71,    54,    43,    65,    39,    39,    43,    68,    41,    41,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    66,     5,     5,    54,    66,
       5,    82,    75,    77,    83,     8,    91,    54,    94,    95,
      66,    41,    42,    41,    37,    53,    44,    64,    70,    40,
      39,    41,    40,    39,    41,     5,    88,    36,    53,    41,
      53,    41,   100,    74,    54,    65,    68,    66,    66,    89,
      41,    71,    93,    99,    54,    37,    41,    41,    43,    86,
      37,    95,    42,     5,    78,    99,    87,    76,    86
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    55,
      55,    55,    55,    55,    55,    55,    55,    56,    57,    57,
      57,    57,    57,    58,    58,    58,    58,    59,    59,    59,
      59,    60,    60,    60,    61,    61,    62,    63,    64,    65,
      65,    66,    66,    67,    67,    68,    68,    69,    70,    71,
      71,    73,    74,    72,    75,    76,    78,    77,    79,    79,
      80,    82,    81,    83,    84,    85,    85,    85,    85,    85,
      85,    87,    86,    86,    89,    88,    88,    90,    91,    92,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       2,     2,     2,     2,     2,     2,     1,     3,     1,     1,
       1,     3,     1,     1,     2,     2,     1,     3,     4,     3,
       4,     4,     2,     6,     1,     1,     3,     5,     1,     3,
       0,     2,     0,     3,     3,     3,     0,     2,     5,     2,
       0,     0,     0,     5,     0,     0,     0,     6,     1,     0,
       2,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     0,     3,     0,     4,     1,     4,
       2,     0,     0,     3,     1,     3,     3,     0,     0,     7,
       7,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 1402 "yacc.y" /* yacc.c:1646  */
    { printf("program->stmts;\n");}
#line 2804 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 1403 "yacc.y" /* yacc.c:1646  */
    { printf("program->stmt\n");}
#line 2810 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 1405 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->expr;\n");}
#line 2816 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 1406 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->ifstmt\n");}
#line 2822 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 1407 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->whilestmt\n");}
#line 2828 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 1408 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->forstmt\n");}
#line 2834 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 1409 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->returnstmt\n");}
#line 2840 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 1410 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->break;\n");
				if(loopcounter!=0){
					push_last(&BreakStack, makeBreakStruct(nextquadlabel())); 
					emit(jump, NULL, NULL, NULL, yylineno);
				}else{
					yyerror("BREAK not in a loop");
				}
			}
#line 2853 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 1419 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->continue;\n");
				if(loopcounter!=0){
					push_last(&ContinueStack, makeContinueStruct(nextquadlabel())); 
					emit(jump, NULL, NULL, NULL, yylineno);
				}else{
					yyerror("CONTINUE not in a loop");
				}
			}
#line 2866 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 1427 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->block;\n");}
#line 2872 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 1428 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->fundef;\n");}
#line 2878 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 1429 "yacc.y" /* yacc.c:1646  */
    {printf("stmt->;\n");}
#line 2884 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 1431 "yacc.y" /* yacc.c:1646  */
    {printf("expr -> assignexpr\n");(yyval.exprNode)=(yyvsp[0].exprNode);}
#line 2890 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 1432 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr or expr\n"); (yyval.exprNode)=logbool(or, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));}
#line 2896 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 1433 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr and expr\n"); (yyval.exprNode)=logbool(and, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));}
#line 2902 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 1434 "yacc.y" /* yacc.c:1646  */
    {	printf("expr->expr + expr\n");
							 	(yyval.exprNode) = arithmetic(add, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));
							 }
#line 2910 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 1437 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr - expr\n");
							 	(yyval.exprNode) = arithmetic(sub, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));
							 }
#line 2918 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 1440 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr * expr\n");
							 	(yyval.exprNode) = arithmetic(mul, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));
							 }
#line 2926 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 1443 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr / expr\n");
							 	(yyval.exprNode) = arithmetic(diV, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));
							 }
#line 2934 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 1446 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr mod expr\n");
							 	(yyval.exprNode) = arithmetic(mod, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));
							 }
#line 2942 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 1449 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr == expr\n");(yyval.exprNode)=relbool(if_eq, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));}
#line 2948 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 1450 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr != expr\n");(yyval.exprNode)=relbool(if_noteq, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));}
#line 2954 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 1451 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr > expr\n");(yyval.exprNode)=relbool(if_greater, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));}
#line 2960 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 1452 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr >= expr\n");(yyval.exprNode)=relbool(if_greatereq, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));}
#line 2966 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 1453 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr <= expr\n");(yyval.exprNode)=relbool(if_lesseq, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));}
#line 2972 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 1454 "yacc.y" /* yacc.c:1646  */
    {printf("expr->expr < expr\n");(yyval.exprNode)=relbool(if_less, (yyvsp[-2].exprNode), (yyvsp[0].exprNode));}
#line 2978 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 1455 "yacc.y" /* yacc.c:1646  */
    {printf("expr->term\n"); (yyval.exprNode)=(yyvsp[0].exprNode);}
#line 2984 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 1458 "yacc.y" /* yacc.c:1646  */
    {printf("term-> ( expr )\n");(yyval.exprNode)=(yyvsp[-1].exprNode);}
#line 2990 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 1460 "yacc.y" /* yacc.c:1646  */
    {
				checkuminus((yyvsp[0].exprNode));
				(yyval.exprNode)=newexpr(arithexpr_e);
				(yyval.exprNode)->sym=istempexpr((yyvsp[0].exprNode))?(yyvsp[0].exprNode)->sym:newtemp();
				emit(uminus,(yyvsp[0].exprNode), NULL, (yyval.exprNode), yylineno);
				printf("term->- expr\n");
			}
#line 3002 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 1467 "yacc.y" /* yacc.c:1646  */
    {
				
				(yyval.exprNode)=newexpr(boolexpr_e);
				(yyval.exprNode)->sym=newtemp();
				emit(not,(yyvsp[0].exprNode),NULL,(yyval.exprNode),yylineno);

				printf("term-> not expr\n");
			}
#line 3015 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 1475 "yacc.y" /* yacc.c:1646  */
    {
 		 		if( (yyvsp[0].exprNode) != NULL ){
						if ((yyvsp[0].exprNode)->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ((yyvsp[0].exprNode)->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

				if ((yyvsp[0].exprNode)->type==tableitem_e){
					(yyval.exprNode)=emit_iftableitem((yyvsp[0].exprNode));
					emit(add,(yyval.exprNode),newexpr_constnum(1),(yyval.exprNode),yylineno);
					emit(tablesetelem,(yyvsp[0].exprNode),(yyvsp[0].exprNode)->index,(yyval.exprNode),yylineno);
				}
				else{
					emit(add,(yyvsp[0].exprNode),newexpr_constnum(1),(yyvsp[0].exprNode),yylineno);
					(yyval.exprNode)=newexpr(arithexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(assign,(yyvsp[0].exprNode),NULL,(yyval.exprNode),yylineno);
				}


 		 		printf("term->++lvalue\n");}
#line 3043 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 1498 "yacc.y" /* yacc.c:1646  */
    {

 		 		if( (yyvsp[-1].exprNode) != NULL ){
						if ((yyvsp[-1].exprNode)->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ((yyvsp[-1].exprNode)->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

				(yyval.exprNode)=newexpr(var_e);
				(yyval.exprNode)->sym=newtemp();

				if ((yyvsp[-1].exprNode)->type==tableitem_e) {
					
					(yyvsp[-1].exprNode)=emit_iftableitem((yyvsp[-1].exprNode));
					emit(assign,(yyvsp[-1].exprNode),NULL, (yyval.exprNode), yylineno);
					emit(add,(yyvsp[-1].exprNode),newexpr_constnum(1),(yyvsp[-1].exprNode),yylineno);
					emit(tablesetelem,(yyvsp[-1].exprNode),(yyvsp[-1].exprNode)->index,(yyvsp[-1].exprNode),yylineno);
				}
				else{

					emit(assign,(yyvsp[-1].exprNode),NULL,(yyval.exprNode),yylineno);
					emit(add,(yyvsp[-1].exprNode),newexpr_constnum(1),(yyvsp[-1].exprNode),yylineno);
				}	

 		 		printf("term-> lvalue++\n");}
#line 3075 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 1525 "yacc.y" /* yacc.c:1646  */
    {

 		 		if( (yyvsp[0].exprNode) != NULL ){
						if ((yyvsp[0].exprNode)->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ((yyvsp[0].exprNode)->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

				if ((yyvsp[0].exprNode)->type==tableitem_e){
					(yyval.exprNode)=emit_iftableitem((yyvsp[0].exprNode));
					emit(add,(yyval.exprNode),newexpr_constnum(1),(yyval.exprNode),yylineno);
					emit(tablesetelem,(yyvsp[0].exprNode),(yyvsp[0].exprNode)->index,(yyval.exprNode),yylineno);
				}
				else{
					emit(sub,(yyvsp[0].exprNode),newexpr_constnum(1),(yyvsp[0].exprNode),yylineno);
					(yyval.exprNode)=newexpr(arithexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(assign,(yyvsp[0].exprNode),NULL,(yyval.exprNode),yylineno);
				}

 		 		printf("term-> --lvalue\n");}
#line 3103 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 1548 "yacc.y" /* yacc.c:1646  */
    {

 		 		if( (yyvsp[-1].exprNode) != NULL ){
						if ((yyvsp[-1].exprNode)->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ((yyvsp[-1].exprNode)->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

				(yyval.exprNode)=newexpr(var_e);
				(yyval.exprNode)->sym=newtemp();


				if ((yyvsp[-1].exprNode)->type==tableitem_e) {
					
					(yyvsp[-1].exprNode)=emit_iftableitem((yyvsp[-1].exprNode));
					emit(assign,(yyvsp[-1].exprNode),NULL, (yyval.exprNode), yylineno);
					emit(add,(yyvsp[-1].exprNode),newexpr_constnum(1),(yyvsp[-1].exprNode),yylineno);
					emit(tablesetelem,(yyvsp[-1].exprNode),(yyvsp[-1].exprNode)->index,(yyvsp[-1].exprNode),yylineno);
				}
				else{

					emit(assign,(yyvsp[-1].exprNode),NULL,(yyval.exprNode),yylineno);
					emit(sub,(yyvsp[-1].exprNode),newexpr_constnum(1),(yyvsp[-1].exprNode),yylineno);
				}	

 		 		printf("term-> lvalue--\n");}
#line 3136 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 1576 "yacc.y" /* yacc.c:1646  */
    {printf("term-> primary\n"); (yyval.exprNode)=(yyvsp[0].exprNode);}
#line 3142 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 1578 "yacc.y" /* yacc.c:1646  */
    {


					if( (yyvsp[-2].exprNode) != NULL ){
						if ((yyvsp[-2].exprNode)->type == programfunc_e){
							yyerror("user function as lvalue");
						}else if ((yyvsp[-2].exprNode)->type == libraryfunc_e){
							yyerror("lib function as lvalue");
						}
					}

					printf("assginexpr -> lvalue = expr\n");

					if((yyvsp[-2].exprNode)->type == tableitem_e){
						emit(tablesetelem, (yyvsp[-2].exprNode), (yyvsp[-2].exprNode)->index, (yyvsp[0].exprNode), yylineno);
						(yyval.exprNode) = emit_iftableitem((yyvsp[-2].exprNode));
						(yyval.exprNode)->type = assignexpr_e;
					}else{
						emit(assign, (yyvsp[0].exprNode), (expr*)0, (yyvsp[-2].exprNode), yylineno);
						(yyval.exprNode) = newexpr(assignexpr_e);
						(yyval.exprNode)->sym = newtemp();
						emit(assign, (yyvsp[-2].exprNode), (expr*)0, (yyval.exprNode),yylineno);
					}														

			}
#line 3172 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1605 "yacc.y" /* yacc.c:1646  */
    {printf("primary->lvalue\n"); (yyval.exprNode)=emit_iftableitem((yyvsp[0].exprNode));}
#line 3178 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1606 "yacc.y" /* yacc.c:1646  */
    {printf("primary->call\n");}
#line 3184 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1607 "yacc.y" /* yacc.c:1646  */
    {printf("primary->objecrdef\n");}
#line 3190 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1609 "yacc.y" /* yacc.c:1646  */
    {
				(yyval.exprNode)=newexpr(programfunc_e);
				(yyval.exprNode)->sym=(yyvsp[-1].symbolNode);

				printf("primary->(funcdef)\n");

			}
#line 3202 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1616 "yacc.y" /* yacc.c:1646  */
    {printf("primary->const\n");}
#line 3208 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1618 "yacc.y" /* yacc.c:1646  */
    {

					SymbolTableEntry  *tmp ;

					int scope1 = scope;

					while(scope1>=0 && (tmp=lookupScope(yytext,scope1)) == NULL){
						scope1--;
					}

					if(tmp!=NULL){
						(yyval.exprNode) = lvalue_expr(tmp);
						//anaferome ekei
					}else if(scope ==0){
						insert(yytext,var_s, currscopespace(), currscopeoffset() );
						inccurrscopeoffset();
						(yyval.exprNode) = lvalue_expr(lookupScope(yytext,0));
					}else{
						insert(yytext,var_s, currscopespace(), currscopeoffset() );
						inccurrscopeoffset();
						(yyval.exprNode) = lvalue_expr(lookupScope(yytext,scope));
					}


				printf("lvalue->id\n");}
#line 3238 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1643 "yacc.y" /* yacc.c:1646  */
    {
					
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
						(yyval.exprNode) = lvalue_expr(lookupScope(yytext, scope));

					}else{
						(yyval.exprNode) = lvalue_expr(tmp);
						//vrikame metavliti i synartisi kai anaferomaste ekei
					}

							printf("lvalue->local id\n");}
#line 3268 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1668 "yacc.y" /* yacc.c:1646  */
    {


					SymbolTableEntry  *tmp = lookupScope(yytext, 0);

					if(tmp==NULL){
						yyerror("global variable not found");
					}else{
						//ANAFEROMASTE EKEI
						(yyval.exprNode) = lvalue_expr(tmp);
					}



					printf("lvalue->::id\n");}
#line 3288 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1683 "yacc.y" /* yacc.c:1646  */
    {printf("lvalue->member\n"); (yyval.exprNode)=(yyvsp[0].exprNode);}
#line 3294 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1685 "yacc.y" /* yacc.c:1646  */
    {
				(yyval.exprNode)=member_item((yyvsp[-2].exprNode),(yyvsp[0].strVal));
				printf("member->lvalue . id\n");
			}
#line 3303 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1689 "yacc.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].exprNode) = emit_iftableitem((yyvsp[-3].exprNode));
				(yyval.exprNode) = newexpr(tableitem_e);
				(yyval.exprNode)->sym = (yyvsp[-3].exprNode)->sym;
				(yyval.exprNode)->index=(yyvsp[-1].exprNode);
				printf("member->lvalue  [expr] \n");
			}
#line 3315 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1696 "yacc.y" /* yacc.c:1646  */
    {
				(yyval.exprNode)=member_item((yyvsp[-2].exprNode),(yyvsp[0].strVal));
				printf("member->call . id\n");
			}
#line 3324 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1700 "yacc.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].exprNode) = emit_iftableitem((yyvsp[-3].exprNode));
				(yyval.exprNode) = newexpr(tableitem_e);
				(yyval.exprNode)->sym = (yyvsp[-3].exprNode)->sym;
				(yyval.exprNode)->index=(yyvsp[-1].exprNode);
				printf("member-> call  [expr] \n");
			}
#line 3336 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1708 "yacc.y" /* yacc.c:1646  */
    {
				printf("call->call ( elist )\n");
				(yyval.exprNode) = make_call((yyvsp[-3].exprNode), NULL);
			}
#line 3345 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1712 "yacc.y" /* yacc.c:1646  */
    {
				printf("call-> lvalue callsuffix\n");
				if ((yyvsp[0].callsuNode)->method){
					expr* self = (yyvsp[-1].exprNode);
					(yyvsp[-1].exprNode) = emit_iftableitem(member_item(self, (yyvsp[0].callsuNode)->name));
					
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
				(yyval.exprNode) = make_call((yyvsp[-1].exprNode), NULL);
			}
#line 3368 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1730 "yacc.y" /* yacc.c:1646  */
    {
				printf("call->( funcdef) ( elist )\n");
				expr* func = newexpr(programfunc_e);
				func->sym =(yyvsp[-4].symbolNode);
				(yyval.exprNode) = make_call(func, NULL);
			}
#line 3379 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1737 "yacc.y" /* yacc.c:1646  */
    {printf("callsuffix -> normcall\n"); (yyval.callsuNode) = (yyvsp[0].callsuNode);}
#line 3385 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1738 "yacc.y" /* yacc.c:1646  */
    {printf("callsuffix -> methodcall\n"); (yyval.callsuNode) = (yyvsp[0].callsuNode);}
#line 3391 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1740 "yacc.y" /* yacc.c:1646  */
    {
					printf("normcall -> ( elist )\n");
					
					//$methodcall.elist = $4;

					(yyval.callsuNode) = (struct callsu*)calloc(1, sizeof(struct callsu));
					(yyval.callsuNode)->method = false;
					(yyval.callsuNode)->name = NULL;
			}
#line 3405 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1750 "yacc.y" /* yacc.c:1646  */
    {
					printf("methodcall ->.. id ( elist )\n");
					//$methodcall.elist = $4;
					(yyval.callsuNode) = (struct callsu*)calloc(1, sizeof(struct callsu));
					(yyval.callsuNode)->method = true;
					(yyval.callsuNode)->name = (yyvsp[-3].strVal);
				}
#line 3417 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1758 "yacc.y" /* yacc.c:1646  */
    { push_first(&ElistStack, makeElistStruct((yyvsp[0].exprNode))); }
#line 3423 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1760 "yacc.y" /* yacc.c:1646  */
    {}
#line 3429 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1761 "yacc.y" /* yacc.c:1646  */
    {}
#line 3435 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1763 "yacc.y" /* yacc.c:1646  */
    {printf("[ expr [, expr] * ]\n");}
#line 3441 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1764 "yacc.y" /* yacc.c:1646  */
    {}
#line 3447 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1767 "yacc.y" /* yacc.c:1646  */
    {printf("objectdef ->[ elist ]\n");

			expr * t = newexpr(newtable_e);
			
			t->sym = newtemp();
			emit(tablecreate,t,NULL,NULL,yylineno);
			int i;
			expr * x;
			for(i=ElistStack.count;(x = getElist(pop(&ElistStack)))!=NULL;i--){
				emit(tablesetelem,t,newexpr_constnum(i-1),x, yylineno);
			}

			(yyval.exprNode)=t;



			}
#line 3469 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1784 "yacc.y" /* yacc.c:1646  */
    {printf("objectdef -> [ indexed ]\n");
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
													(yyval.exprNode) = t;
			}
#line 3494 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1806 "yacc.y" /* yacc.c:1646  */
    {}
#line 3500 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1807 "yacc.y" /* yacc.c:1646  */
    {}
#line 3506 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1810 "yacc.y" /* yacc.c:1646  */
    {printf("[indexedelem [, indexedelem] * ]\n");

}
#line 3514 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1814 "yacc.y" /* yacc.c:1646  */
    {printf("indexedelem -> { expr : expr }\n");
push_last(&IndexedStack, makeIndexedStruct((yyvsp[-3].exprNode),(yyvsp[-1].exprNode)));}
#line 3521 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1817 "yacc.y" /* yacc.c:1646  */
    {}
#line 3527 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1818 "yacc.y" /* yacc.c:1646  */
    {}
#line 3533 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1820 "yacc.y" /* yacc.c:1646  */
    {scope++;}
#line 3539 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1820 "yacc.y" /* yacc.c:1646  */
    {hide(scope);scope--;}
#line 3545 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1820 "yacc.y" /* yacc.c:1646  */
    {printf(" stmt*\n");}
#line 3551 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1822 "yacc.y" /* yacc.c:1646  */
    {push_last(&loopcounterStack, makeLoopcounterStruct(loopcounter)); loopcounter=0; }
#line 3557 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1824 "yacc.y" /* yacc.c:1646  */
    { loopcounter = getLoopcounter(pop(&loopcounterStack)); }
#line 3563 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1826 "yacc.y" /* yacc.c:1646  */
    {hide(scope);scope--;}
#line 3569 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1828 "yacc.y" /* yacc.c:1646  */
    {
	
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
				(yyval.strVal) = strdup(yytext);
			}
		}
}
#line 3594 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1847 "yacc.y" /* yacc.c:1646  */
    {
	
		static int functioncounter = 0;
		char *func = malloc(10);
		sprintf(func, "%s%d", "_f", functioncounter++);
		(yyval.strVal) = func;
		insert(func,programfunc_s, currscopespace(), currscopeoffset() );
		//inccurrscopeoffset();
}
#line 3608 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1859 "yacc.y" /* yacc.c:1646  */
    {
	(yyval.symbolNode)=lookupScope((yyvsp[0].strVal), scope);
	(yyval.symbolNode)->iaddress=nextquadlabel();
	emit(funcstart,NULL,NULL,lvalue_expr((yyval.symbolNode)), yylineno);
	
	push_last(&functionLocalsStack, makeFunctionLocalOffsetStruct(functionLocalOffset));
	enterscopespace();
	resetformalargsoffset();
}
#line 3622 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1869 "yacc.y" /* yacc.c:1646  */
    {scope++;}
#line 3628 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1870 "yacc.y" /* yacc.c:1646  */
    {
	enterscopespace();
	resetfunctionlocaloffset();
}
#line 3637 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1876 "yacc.y" /* yacc.c:1646  */
    {
	exitscopespace();	
}
#line 3645 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1881 "yacc.y" /* yacc.c:1646  */
    {
	exitscopespace();
	(yyvsp[-2].symbolNode)->totallocals=functionLocalOffset;
	
	functionLocalOffset = getFunctionLocalOffset(pop(&functionLocalsStack));
	
	(yyval.symbolNode)=(yyvsp[-2].symbolNode);

	emit(funcend,NULL,NULL,lvalue_expr((yyvsp[-2].symbolNode)), yylineno);
	printf("function id (idlist) block\n");
}
#line 3661 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1893 "yacc.y" /* yacc.c:1646  */
    {printf("const->number\n");(yyval.exprNode)=newexpr_constnum((yyvsp[0].intVal));}
#line 3667 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1894 "yacc.y" /* yacc.c:1646  */
    {printf("const->number\n");(yyval.exprNode)=newexpr_constnum((yyvsp[0].realVal));}
#line 3673 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1895 "yacc.y" /* yacc.c:1646  */
    {printf("const->string\n");(yyval.exprNode)=newexpr_conststring((yyvsp[0].strVal));}
#line 3679 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1896 "yacc.y" /* yacc.c:1646  */
    {printf("const->nil\n");(yyval.exprNode)=newexpr(nil_e);}
#line 3685 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1897 "yacc.y" /* yacc.c:1646  */
    {printf("const->true\n");(yyval.exprNode)=newexpr_constbool(true);}
#line 3691 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1898 "yacc.y" /* yacc.c:1646  */
    {printf("cost->false\n");(yyval.exprNode)=newexpr_constbool(false);}
#line 3697 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1900 "yacc.y" /* yacc.c:1646  */
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
#line 3715 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1912 "yacc.y" /* yacc.c:1646  */
    {}
#line 3721 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1913 "yacc.y" /* yacc.c:1646  */
    {}
#line 3727 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1916 "yacc.y" /* yacc.c:1646  */
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
#line 3745 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1930 "yacc.y" /* yacc.c:1646  */
    {printf("\n");}
#line 3751 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1931 "yacc.y" /* yacc.c:1646  */
    {}
#line 3757 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1934 "yacc.y" /* yacc.c:1646  */
    {
				emit_label(if_eq, (yyvsp[-1].exprNode), newexpr_constbool(1),NULL, nextquadlabel()+2, yylineno);
				(yyval.intVal) = nextquadlabel();
				emit(jump, NULL, NULL, NULL, yylineno);
			}
#line 3767 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1940 "yacc.y" /* yacc.c:1646  */
    {
				(yyval.intVal) = nextquadlabel();
				emit(jump, NULL, NULL, NULL, yylineno);
			}
#line 3776 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1945 "yacc.y" /* yacc.c:1646  */
    {
				patchlabel((yyvsp[-3].intVal),(yyvsp[-1].intVal)+1);
				patchlabel((yyvsp[-1].intVal), nextquadlabel());}
#line 3784 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1948 "yacc.y" /* yacc.c:1646  */
    {
				patchlabel((yyvsp[-1].intVal), nextquadlabel());
			}
#line 3792 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1952 "yacc.y" /* yacc.c:1646  */
    {loopcounter--;}
#line 3798 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1953 "yacc.y" /* yacc.c:1646  */
    {loopcounter++; ElistStack.head = ElistStack.tail = NULL; ElistStack.count = 0;}
#line 3804 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1955 "yacc.y" /* yacc.c:1646  */
    { /*$$ = $2;*/ }
#line 3810 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1957 "yacc.y" /* yacc.c:1646  */
    {
						(yyval.intVal) = nextquadlabel();
				}
#line 3818 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1961 "yacc.y" /* yacc.c:1646  */
    {
					emit_label(if_eq, (yyvsp[-1].exprNode), newexpr_constbool(1), NULL,nextquadlabel()+2, yylineno);
					(yyval.intVal) = nextquadlabel();
					emit(jump, NULL, NULL, NULL, yylineno);
													 }
#line 3828 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1967 "yacc.y" /* yacc.c:1646  */
    {
					emit_label(jump, NULL, NULL, NULL, (yyvsp[-2].intVal), yylineno);
					patchlabel((yyvsp[-1].intVal), nextquadlabel());
					
					
																
																//patchlabel(stmt.contlist, $2+1);		
																void *elem = top(&ContinueStack);
																int i,l;
																while(elem != NULL){
																	l = getContinueL(elem);
																	if(l == (loopcounter+1)){
																		i = getContinueI(elem);
																		patchlabel(i, (yyvsp[-2].intVal));
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
#line 3871 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 2006 "yacc.y" /* yacc.c:1646  */
    {
					(yyval.intVal) = nextquadlabel();
					emit(jump, NULL, NULL, NULL, yylineno);
				}
#line 3880 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 2011 "yacc.y" /* yacc.c:1646  */
    {
					(yyval.intVal) = nextquadlabel();
				}
#line 3888 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 2015 "yacc.y" /* yacc.c:1646  */
    {
																		(yyval.forrNode) = calloc(1, sizeof(struct forr));
																		(yyval.forrNode)->test = (yyvsp[-2].intVal);
																		(yyval.forrNode)->enter = nextquadlabel();
																		emit(if_eq, (yyvsp[-1].exprNode), newexpr_constbool(1), NULL, yylineno);
																    }
#line 3899 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 2022 "yacc.y" /* yacc.c:1646  */
    {
																patchlabel((yyvsp[-6].forrNode)->enter, (yyvsp[-2].intVal)+1);
																patchlabel((yyvsp[-5].intVal), nextquadlabel());
																patchlabel((yyvsp[-2].intVal), (yyvsp[-6].forrNode)->test);
																patchlabel((yyvsp[0].intVal), (yyvsp[-5].intVal)+1);

																int i;
																int l;


																void * elem = top(&ContinueStack);

																//patchlabel(stmt.contlist, $2+1);
																while(elem != NULL){
																	l = getContinueL(elem);
																	if(l == (loopcounter+1)){
																		i = getContinueI(elem);
																		patchlabel(i, (yyvsp[-5].intVal)+1);
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
#line 3947 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 2066 "yacc.y" /* yacc.c:1646  */
    {
				if(functionlocal == currscopespace())
					emit(ret,(yyvsp[-1].exprNode),NULL,NULL,yylineno);
				else
					yyerror("RETURN not in a function");

				printf("returnstmt -> return expr;\n");
			}
#line 3960 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 2074 "yacc.y" /* yacc.c:1646  */
    {
				if(functionlocal == currscopespace())
					emit(ret,NULL,NULL,NULL,yylineno);
				else
					yyerror("RETURN not in a function");
				printf("returnstmt -> return ;\n");
			}
#line 3972 "yacc.tab.c" /* yacc.c:1646  */
    break;


#line 3976 "yacc.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2083 "yacc.y" /* yacc.c:1906  */



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

