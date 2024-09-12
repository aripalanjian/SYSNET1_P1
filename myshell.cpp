#include "myshell.hpp"
#define MAXARGS 32
#include <iostream>
#include <string.h>

Shell::Shell(int argC, char **argV){
    this->argC = argC;
    this->argV = argV;
    checkOptions();
}

void Shell::run(){
    using std::cout; using std::endl;

    int exitCode;
    char* tokens[MAXARGS];

    cout << prompt;
    int count = getInput(tokens);
    while (true){
        
        exitCode = parser.parseTokens(count, tokens);
        
        if (debug){
            // printParams();
            cout << "Number of tokens: " << count << endl;
            for (int i = 0; i < count; i++){
                //for loop for debuging tokens
                cout << i << ": " << tokens[i] << ", ";
            }
            cout << endl;
        }

        if (exitCode == 0) {
            break;
        } else if (exitCode == -1){
            //record error
            // break;
        }
        cout << "\n" << prompt;
        count = getInput(tokens);
    }

    for (int i = 0; i < count; i++){
        delete tokens[i];
    }
}

int Shell::getInput(char **arr){
    char *input, *temp;
    std::cin.getline(input,1000);
    std::stringstream ss(input);

    int i = 0;
    while (!ss.eof()){
        temp = new char;
        ss >> temp;
        arr[i++] = temp;
    }

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