# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -O3

default: main

ABB.o: ABB.c ABB-privado.h ABB-publico.h
	$(CC) $(CFLAGS) -c ABB.c -o ABB.o

main: main.c ABB.o
	$(CC) $(CFLAGS) main.c ABB.o -o main

clean:
	rm -f main *.o core a.out *.*~ Makefile~

all: main