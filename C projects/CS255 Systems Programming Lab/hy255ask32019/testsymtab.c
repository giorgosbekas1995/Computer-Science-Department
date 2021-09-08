#include "symtable.h"

int main(){
	
	
	SymTable_T a=NULL;

	a=SymTable_new();
	
	printf("%d",SymTable_put(a,"a",(int*) 4));
	printf("%d  ",SymTable_put(a,"b",(int*) 4));
	
	printf("%d  ",SymTable_getLength(a));

  	printf("%d  ",(int)SymTable_get(a,"a"));
	printf("%d  ",SymTable_get(a,"b"));
	printf("%d  ",SymTable_contains(a,"b"));
  	SymTable_remove(a,"b");
 	printf("%d  ",SymTable_getLength(a));
 	/*SymTable_free(a);*/ 
	return 0;
}
