CFLAGS = -g -Wall
CC = g++

objects = myshell.o param.o parse.o

myshell: $(objects)
	$(CC) -o myshell $(objects)

myshell.o: myshell.cpp param.cpp parse.cpp

.PHONY : clean
clean: 
	rm myshell $(objects)