all: cs340
cs340: yacc.tab.o al.o vm.o 
	gcc -g yacc.tab.o al.o -o phasi4
	gcc -g vm.o -o vm

yacc.tab.o: yacc.tab.c
	gcc -g -c yacc.tab.c

yacc.tab.c: yacc.y
	bison -v -d yacc.y

al.o: al.c
	gcc -g -c al.c
al.c: al.l
	flex -o al.c al.l

vm.o: vm.c
	gcc -g -c vm.c

clean:
	rm -rf vm vm.o yacc.tab.h phasi4 al.o al.c yacc.tab.o yacc.tab.c yacc.output

