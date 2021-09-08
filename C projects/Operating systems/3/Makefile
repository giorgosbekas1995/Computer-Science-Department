# Giorgos Bekas
# makefile for C grocery, Operating Systems
OFLAGS= -Wall -lpthread -lrt #     # object files parameters  
CFLAGS= -Wall -lpthread -lrt  -c# .c files parameters	
CC=gcc -g   -D _BSD_SOURCE -D __USE_XOPEN #				     # compiler
	
#grocery
all:grocery

# grocery output
grocery: grocery.o
	$(CC)  $(OFLAGS) -o grocery  grocery.o -pthread

grocery.o: grocery.c
	$(CC)  $(CFLAGS) grocery.c  -pthread

#clean object files and outputs
clean:
	rm -rf *.o
	rm -rf grocery