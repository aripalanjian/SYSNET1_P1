#ifndef PARSE_HPP
#define PARSE_HPP

#include "param.hpp"

class Parse{
    Param *params;
public:
    Parse();
    ~Parse();
    int parseTokens(int count, char **tokens);
    Param* getParams();
    int exit();
    int abort();
};

#endif