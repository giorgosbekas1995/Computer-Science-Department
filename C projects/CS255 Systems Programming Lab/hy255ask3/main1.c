#include <stdio.h>
#include "symtablelist.c"

int main(){
	SymTable_T a=NULL;
	
	
	a=SymTable_new();
	printf("%d",SymTable_put(a,"fadgs",(int*) 4));
	printf("%d",SymTable_put(a,"dsfh",(int*) 4));
	printf("%d",SymTable_put(a,"fadg",(int*) 4));


	printf("%d",SymTable_getLength(a));

	printf("%d",(int)SymTable_get(a,"fadg"));

	return 0;
}
