CFLAGS = -g -Wall
CC = g++

objects = myshell.o param.o parse.o

myshell: $(objects)
	$(CC) -o main $(objects)

myshell.o: myshell.cpp param.cpp parse.cpp

.PHONY : clean
clean: 
	rm main $(objects)