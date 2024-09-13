    // char *inputRedirect; /* file name or NULL */
    // char *outputRedirect; /* file name or NULL */
    // int background; /* either 0 (false) or 1 (true) */
    // int argumentCount; /* number of tokens in argument vector */
    // char *argumentVector[MAXARGS]; /* array of strings */

//     term : The term 'term' is not recognized as the name of a cmdlet, function, script file, or operable program. Check the spelling of the name, or if a path was 
// included, verify that the path is correct and try again.
// At line:1 char:1
// + rust
// + ~~~~
//     + CategoryInfo          : ObjectNotFound: (rust:String) [], CommandNotFoundException
//     + FullyQualifiedErrorId : CommandNotFoundException

#include "param.hpp"
#include <iostream>
#include <string.h>

Param::Param(){
    inputRedirect = outputRedirect = NULL;
    this->background = 0;
}

char* Param::getInputRedirect(){
    return inputRedirect;
}

char* Param::getOutputRedirect(){
    return outputRedirect;
}

int Param::getBackground(){
    return background;
}

int Param::getArgumentCount(){
    return argumentCount;
}

char** Param::getArgumentVector(){
    return argumentVector;
}

void Param::setInputRedirect(char* input){
    this->inputRedirect = input;
}

void Param::setOutputRedirect(char* output){
    this->outputRedirect = output;
}

void Param::setBackground(int background){
    this->background = background;
}

void Param::setArgumentCount(int count){
    this->argumentCount = count;
}

void Param::setArgumentVector(char** arguments){
    // this->argumentVector = arguments;
    for (int i = 0; i < argumentCount; i++){
        this->argumentVector[i] = arguments[i];
    }
}

void Param::printParams(){
    using std::cout; using std::endl;

    cout << "InputRedirect: ["
        << ((inputRedirect != NULL) ? inputRedirect : "NULL");
    cout << "]"
        << endl
        << "OutputRedirect: ["
        << ((outputRedirect != NULL) ? outputRedirect : "NULL");
    cout << "]"
        << endl
        << "Background: ["
        << background
        << "]"
        << endl
        << "ArgumentCount: ["
        << argumentCount
        << "]"
        << endl;
    for (int i = 0; i < argumentCount; i++){
        cout << "ArgumentVector["
        << i
        << "]: ["
        << argumentVector[i]
        << "]"
        << endl;
    }
}

void Param::resetParams(){
    inputRedirect = outputRedirect = NULL;
    background = 0;
    argumentCount = 0;
    for (int i = 0; i < MAXARGS; i++){
        argumentVector[i] = NULL;
    }
}