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


# CC= g++
# DEBUG = -g
# CXXFLAGS = $(DEBUG) -c -Wall -std=c++11
# LDLIBS =


# TARGET = main

# SOURCES = \
# main.cpp myshell.cpp parse.cpp param.cpp

# OBJECTS = $(SOURCES:.cpp=.o)

# $(TARGET): $(OBJECTS)
# 	$(CC) -o $(TARGET) $(OBJECTS) $(LDLIBS)
# 	./main

# .cpp.o:
# 	$(CC) $(CXXFLAGS) $< -o $@

# .PHONY : all $(TARGET)

# clean:
# 	rm -f $(OBJECTS)

# clobber:clean
# 	rm -f $(TARGET)