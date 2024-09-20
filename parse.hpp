/***************************************************************
  Student Name: Ari Palanjian
  File Name: parse.hpp
  Project 1

  Parse class definition
    Take tokens and distribute to appropriate param fields
***************************************************************/
#ifndef PARSE_HPP
#define PARSE_HPP

#include "param.hpp"

class Parse{
    Param *params;
    char errorLog[1000];
    void generateErrorMsg(const char* violator);
    void generateOptionsErrorMsg(const char* violator, const char* command);
public:
    Parse();
    ~Parse();
    int parseTokens(int count, char **tokens);
    Param* getParams();
    bool checkCommands(const char* token);
    char* getErrorLog();
    int exit();
    int abort();
};

#endif