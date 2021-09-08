# Giorgos Bekas
# makefile for C shell, Operating Systems
OFLAGS= -Wall -pedantic#     # object files parameters  
CFLAGS= -Wall -pedantic -c   # .c files parameters	
CC=gcc #				     # compiler
	
#shell
all:myshell

# shell output
myshell: shell.o
	$(CC) $(OFLAGS) -o myshell  shell.o

shell.o: shell.c
	$(CC) $(CFLAGS) shell.c

#clean object files and outputs
clean:
	rm -rf *.o
	rm -rf myshell