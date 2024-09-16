#ifndef MYSHELL_HPP
#define MYSHELL_HPP

#include "parse.hpp"

class Shell{
    const char* prompt = "$$$ ";
    Parse parser = Parse();
    int argC;
    char ** argV;
    bool debug;
    void checkOptions();
public:
    Shell(int argC, char **argV);
    void run();
    int getInput(char **arr);
};

#endif