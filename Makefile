CFLAGS=-Wall -g -lgc

all: main

main: vector.o

test:
	gcc $(CFLAGS) -c -o vector.o vector.c
	gcc $(CFLAGS) basic_test.c vector.o -lcmocka -o test

clean:
	rm -f main test vector.o
