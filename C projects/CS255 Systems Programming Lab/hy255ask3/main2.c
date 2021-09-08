#include <stdio.h>
#include "symtablehash.c"

int main(){
	SymTable_T a=NULL;
	
	
	a=SymTable_new();
	printf("%d",SymTable_put(a,"fadgs",(int*) 4));
	printf("%d",SymTable_put(a,"dsfh",(int*) 4));
	
	return 0;
}
