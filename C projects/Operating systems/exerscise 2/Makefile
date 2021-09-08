# Giorgos Bekas
# makefile for C consumers, Operating Systems
OFLAGS= -Wall -pthread -std=c11#     # object files parameters  
CFLAGS= -Wall -pthread -std=c11 -c# .c files parameters	
CC=gcc -g #				     # compiler
	
#consumers
all:consumers

# consumers output
consumers: consumers.o defines.h
	$(CC) $(OFLAGS) -o consumers  consumers.o

consumers.o: consumers.c defines.h
	$(CC) $(CFLAGS) consumers.c

#clean object files and outputs
clean:
	rm -rf *.o
	rm -rf consumers