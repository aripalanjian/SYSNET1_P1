CFLAGS = -g -Wall
CC = g++

objects = myshell.o param.o parse.o

all: myshell slow

myshell: $(objects)
	$(CC) -o myshell $(objects)

slow: slow.o
	$(CC) -o slow slow.o

myshell.o: myshell.cpp param.cpp parse.cpp

slow.o: slow.c

.PHONY : clean
clean: 
	rm myshell $(objects)
	rm slow slow.o
	rm testfile.txt