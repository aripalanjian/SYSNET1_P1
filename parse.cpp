/***************************************************************
  Student Name: Ari Palanjian
  File Name: parse.cpp
  Project 1

  Parse class member funtion definitions
***************************************************************/
#include "parse.hpp"
#include <iostream>
#include <string.h>

using std::cout;

Parse::Parse(){
    params = new Param();
}

Parse::~Parse(){
    delete params;
}

int Parse::parseTokens(int count, char **tokens){
    memset(errorLog, 0, 1000);
    if (count == 1 && strcmp(tokens[0],"exit") == 0){
        std::cout << "exiting..."<< std::endl;
        return exit();
    } else if (count > 1 && strcmp(tokens[0],"exit") == 0){
        generateOptionsErrorMsg(tokens[1], "exit");
        return abort();
    }

    if (!checkCommands(tokens[0])){
        generateErrorMsg(tokens[0]);
        return abort();
    }

    int argumentCount = 0;
    char *argumentVector[MAXARGS];

    for(int i = 0; i < count; i++){
        if(tokens[i][0] == '<'){
            if (strcmp(tokens[i], "<") == 0){
                params->setInputRedirect(tokens[i+1]);
                i++;
            } else {
                params->setInputRedirect((tokens[i]+1));
            }
        } else if (tokens[i][0] == '&'){
            params->setBackground(1);
        } else if (tokens[i][0] == '>'){
            if (strcmp(tokens[i], ">") == 0){
                params->setOutputRedirect(tokens[i+1]);
                i++;
            } else {
                params->setOutputRedirect(tokens[i]+1);
            }
        } else {
            argumentVector[argumentCount++] = tokens[i];
        }
    }

    if (argumentCount > 0){
        params->setArgumentCount(argumentCount);
        params->setArgumentVector(argumentVector);
    }
    
    return 1;
}

bool Parse::checkCommands(const char* command){
    const char* commands[] = {"ls", "grep", "cat", "./slow"};
    int size = sizeof(commands)/sizeof(char*);

    for(int i = 0; i < size; i++){
        if (strcmp(command, commands[i]) == 0)
            return true;
    }

    return false;
}

void Parse::generateErrorMsg(const char* violator){
    strcat(errorLog, "Error: The term \'");
    strcat(errorLog, violator);
    strcat(errorLog, "\' is not recognized as a command.");
}

void Parse::generateOptionsErrorMsg(const char* violator, const char* command){
    strcat(errorLog, "Error: The term \'");
    strcat(errorLog, violator);
    strcat(errorLog, "\' is not recognized as an option subsequent to ");
    strcat(errorLog, command);
    strcat(errorLog, ".");
}

Param* Parse::getParams(){
    return params;
}

char* Parse::getErrorLog(){
    return errorLog;
}

int Parse::exit(){

    return 0;
}

int Parse::abort(){

    return -1;
}