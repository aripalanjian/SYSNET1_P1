#include "parse.hpp"
#include <iostream>
#include <string.h>

using std::cout;

Parse::Parse(){
    params = new Param();
    errorLog = new char;
}

Parse::~Parse(){
    delete params;
    delete errorLog;
}

int Parse::parseTokens(int count, char **tokens){
    if (count == 1 && strcmp(tokens[0],"exit") == 0){
        std::cout << "exiting..."<< std::endl;
        return exit();
    } else if (count > 1 && strcmp(tokens[0],"exit") == 0){
        generateErrorMsg(tokens[1], "exit");
        return abort();
    }

    int argumentCount = 0;
    char *argumentVector[MAXARGS];

    for(int i = 0; i < count; i++){
        if(tokens[i][0] == '<'){
            //need to account for > directly after inputRedirect
            if (strcmp(tokens[i], "<") == 0){
                params->setInputRedirect(tokens[i+1]);
                i++;
            } else {
                params->setInputRedirect((tokens[i]+1));
            }
        } else if (tokens[i][0] == '&' && i == count - 1){
            params->setBackground(1);
        } else if (tokens[i][0] == '>'){
            //outputRedirect
            if (strcmp(tokens[i], ">") == 0){
                params->setOutputRedirect(tokens[i+1]);
                i++;
            } else {
                params->setOutputRedirect(tokens[i]+1);
            }
        } else {
            argumentVector[argumentCount++] = tokens[i];
            //add tokens to array
        }
    }

    if (argumentCount > 0){
        params->setArgumentCount(argumentCount);
        params->setArgumentVector(argumentVector);
    }
    
    return 1;
}

void Parse::generateErrorMsg(const char* violator, const char* command){
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