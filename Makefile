CFLAGS = -g -Wall -Wextra
CC = g++

objects = main.o myshell.o param.o parse.o

main: $(objects)
	$(CC) -o main $(objects)

main.o: main.cpp myshell.cpp param.cpp parse.cpp
# myshell.o: myshell.cpp myshell.hpp
# param.o: param.cpp param.hpp
# parse.o: parse.cpp parse.hpp

.PHONY : clean
clean: 
	rm main $(objects)