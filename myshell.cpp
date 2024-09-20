#include "myshell.hpp"
#define MAXARGS 32
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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

    int* status;
    int pid;

    while (true){
        exitCode = parser.parseTokens(count, tokens);
        params = parser.getParams();

        if (exitCode == 0) {
            break;
        } else if (exitCode == -1){
            cout << parser.getErrorLog() << endl;
            //record error
        } else if (!params->getBackground()){
            //call fork here
            pid = fork();
            if (pid == 0) {
                std::cout << "Child Process\n";
                checkParams(params);
                break;
            } else {
                wait(status); //change to waitpid so that new commands cannot be entered until child is done
                std::cout << "Parent Process\n";
                if (debug){
                    params->printParams();
                }
            }
        } else {
            pid = fork();
            if (pid == 0) {
                std::cout << "Child Process\n";
                checkParams(params);
                break;
            } else {
                std::cout << "Parent Process\n";
                if (debug){
                    params->printParams();
                }
            }
        }

        cout << "\n" << prompt;
        count = getInput(tokens);
        params->resetParams();
    }

    wait(status);
    std::cout << "Children should be terminated..." << endl;
}

int Shell::getInput(char **arr){
    char *input;
    input = new char;
    std::cin.getline(input, 1000);
    const char * delim = " \t";
    char* token = strtok(input, delim);

    int i = 0;
    while(token){
        arr[i++] = strdup(token);
        token = strtok(nullptr, delim);
    }

    delete input, token;
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

void Shell::checkParams(Param* params){
    // {"ls", "grep", "cat", "./slow"}
    unsigned size = params->getArgumentCount();
    char** arguments = params->getArgumentVector();
    char* const* option;
    if(size > 1){
        option = arguments + 1;
    } else {
        option = NULL;
    }
    const char* outputRedirect = params->getOutputRedirect();
    const char* inputRedirect = params->getInputRedirect();
    if (strcmp(arguments[0], "ls") == 0){
        if (outputRedirect != NULL){
            freopen(outputRedirect, "w", stdout);
        }
        execvp("/bin/ls", option);
    } else if (strcmp(arguments[0], "grep") == 0){
        //write lines with given word to cout
        execvp(arguments[0], option);
    } else if (strcmp(arguments[0], "cat") == 0){
        // displays the source code of the program on the screen
        const char* file;
        if (inputRedirect != NULL){
            file = inputRedirect;
        } else {
            file = NULL;
            for(int i = 0; i < size - 1; i++){
                if (option[i][0] != '-'){
                    file = option[i];
                }
            }
        }        

        freopen(file, "r", stdin);
        execvp("/bin/cat", option);
        
    } else if (strcmp(arguments[0], "./slow") == 0){
        execvp(arguments[0], option);
            // runs the program slow from the current working directory in the background
    } else {
        //Error message
    }
    // exit(0);
}

int main(int argC, char **argV){
    Shell shell = Shell(argC, argV);
    shell.run();

    return 0;
}