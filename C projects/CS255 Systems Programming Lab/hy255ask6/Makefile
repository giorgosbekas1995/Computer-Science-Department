CC=gcc
OFLAGS=-ansi -Wall -pedantic -o
CFLAGS=-ansi -Wall -pedantic -c
all: data3 data6


data6: createdata6.o
	$(CC) $(OFLAGS) createdata6.out createdata6.o
	createdata6.out

data3 : createdata3.o
	$(CC) $(OFLAGS) createdata3.out createdata3.o
	createdata3.out

createdata6.o: createdata6.c
	$(CC) $(CFLAGS) -c createdata6.c

createdata3.o: createdata3.c
	$(CC) $(CFLAGS) -c createdata3.c

clean:
	rm -rf *.out
	rm -rf *.o
	rm data3
	rm data6
