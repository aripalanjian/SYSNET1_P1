#ifndef PARSE_HPP
#define PARSE_HPP

#include "param.hpp"

class Parse{
    Param *params;
    char *errorLog;
public:
    Parse();
    ~Parse();
    int parseTokens(int count, char **tokens);
    Param* getParams();
    int exit();
    int abort();
    char* getErrorLog();
    void generateErrorMsg(const char* violator, const char* command);
};

#endif