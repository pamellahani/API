CFLAGS= -g -Wall -Werror -O2
CC=gcc

all:main

main: main.o fibo.o
	$(CC) $(CFLAGS) main.o fibo.o -o main -lm

clean:
	rm -f main *.o