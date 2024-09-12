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
    if (count == 1 && strcmp(tokens[0],"exit") == 0){
        std::cout << "exiting..."<< std::endl;
        return exit();
    } else if (count > 1 && strcmp(tokens[0],"exit") == 0){
        std::cout << "Error: The term \'" << tokens[1] << "\' is not recognized as an option subsequent to exit." << std::endl;
        return abort();
    }

    int argumentCount = 0;
    char *argumentVector[32];

    for(int i = 0; i < count; i++){
        if(tokens[i][0] == '<'){
            //need to account for > after inputRedirect
            if (strcmp(tokens[i], "<") == 0){
                std::cout << "1)inputRedirect: " << tokens[i+1] << std::endl;
                params->setInputRedirect(tokens[i+1]);
                i++;
            } else {
                std::cout << "2)inputRedirect: " << tokens[i]+1 << std::endl;
                params->setInputRedirect(tokens[i]+1);
            }
        } else if (tokens[i][0] == '&' && i == count - 1){
            params->setBackground(1);
        } else if (tokens[i][0] == '>'){
            //outputRedirect
        } else {
            argumentVector[argumentCount++] = tokens[i];
            //add tokens to array
        }
    }

    if (argumentCount > 0){
        params->setArgumentCount(argumentCount);
        params->setArgumentVector(argumentVector);
    }
    
    // if () //else if (tokens[0] == "pwd"){
    //     cout << fs.pwd() << endl;
    // } else if (tokens[0] == "cd") {
    //     cout << fs.cd(tokens[1]);
    // } else if (tokens[0] == "touch") {
    //     cout << fs.touch(tokens[1]);
    // } else if (tokens[0] == "ls") {
    //     cout << fs.ls();
    // } else if (tokens[0] == "rm") {
    //     cout << fs.rm(tokens[1]);
    // } else if (tokens[0] == "mv") {
    //     cout << fs.mv(tokens[1],tokens[2]);
    // } else if (tokens[0] == "mkdir") {
    //     cout << fs.mkdir(tokens[1]);
    // }
    return 1;
}

Param* Parse::getParams(){
    return params;
}

int Parse::exit(){

    return 0;
}

int Parse::abort(){

    return -1;
}