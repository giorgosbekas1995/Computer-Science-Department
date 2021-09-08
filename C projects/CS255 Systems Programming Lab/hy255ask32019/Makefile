
CFLAGS = -ansi -Wall -pedantic

symtablehash.o : symtable.h symtablehash.c
	gcc -c symtablehash.c

symtablelist.o: symtable.h symtablelist.c
	gcc -c symtablelist.c
	

Symtablelist: symtable.h symtablelist.o
	gcc $(CFLAGS) -o test testsymtab.c symtablelist.o
	
Symtablehash: symtable.h symtablehash.o
	gcc $(CFLAGS) -o test testsymtab.c symtablehash.o
	
clean:	rm -rf *.o
	rm -rf test	
