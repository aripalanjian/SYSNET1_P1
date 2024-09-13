#include "myshell.hpp"
#define MAXARGS 32
#include <iostream>
#include <string.h>

Shell::Shell(int argC, char **argV){
    this->argC = argC;
    this->argV = argV;
    debug = false;
    checkOptions();
}

void Shell::run(){
    using std::cout; using std::endl;

    int exitCode;
    char* tokens[MAXARGS];

    cout << prompt;
    int count = getInput(tokens);
    Param* params;

    while (true){
        
        exitCode = parser.parseTokens(count, tokens);
        params = parser.getParams();

        if (exitCode == 0) {
            break;
        } else if (exitCode == -1){
            //record error
            // break;
        }

        if (debug){
            params->printParams();
        }
        cout << "\n" << prompt;
        count = getInput(tokens);
        params->resetParams();
    }

    for (int i = 0; i < count; i++){
        delete tokens[i];
    }
}

int Shell::getInput(char **arr){
    char *input, *temp;
    input = new char;
    std::cin.getline(input, 1000);
    std::stringstream ss(input);

    int i = 0;
    while (!ss.eof()){
        temp = new char;
        ss >> temp;
        arr[i++] = temp;
    }

    delete input;
    return i;
}

void Shell::checkOptions(){
    for(int i = 0; i < argC; i++){
        if (strcmp(argV[i], "-Debug") == 0){
            debug = true;
            std::cout << "Shell initialized in debug mode." << std::endl;
        }
    }
}