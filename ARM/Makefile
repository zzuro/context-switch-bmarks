CC = gcc 
CFLAGS = -Wall -Wextra -g 

all: main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

switch.o: switch.S
	$(CC) $(CFLAGS) -c switch.S -o switch.o

main: main.o switch.o
	$(CC) $(CFLAGS) main.o switch.o -o main 

clean:
	rm -f *.o main