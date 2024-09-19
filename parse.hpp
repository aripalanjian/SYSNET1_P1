#ifndef PARSE_HPP
#define PARSE_HPP

#include "param.hpp"

class Parse{
    Param *params;
    char errorLog[1000];
    void generateErrorMsg(const char* violator, const char* command);
public:
    Parse();
    ~Parse();
    int parseTokens(int count, char **tokens);
    Param* getParams();
    char* getErrorLog();
    int exit();
    int abort();
};

#endif