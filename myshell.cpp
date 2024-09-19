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
        parser = Parse();
        exitCode = parser.parseTokens(count, tokens);
        params = parser.getParams();

        if (exitCode == 0) {
            break;
        } else if (exitCode == -1){
            cout << parser.getErrorLog() << endl;
            //record error
            // break;
        } //else {
            //call fork here
        pid = fork();
        if (pid == 0) {
            std::cout << "Child Process\n";
            // checkParams(params);
            break;
        } else {
            wait(status); //change to waitpid so that new commands cannot be entered until child is done
            std::cout << "Parent Process\n";
            if (debug){
                params->printParams();
            }
            cout << "\n" << prompt;
            count = getInput(tokens);
            params->resetParams();
        }
        //}
    }
    
    if (pid != 0){

        // for (int i = 0; i < count; i++){
        //     delete tokens[i];
        // }
    }
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

    if (strcmp(arguments[0], "ls") == 0){
        execv("/bin/ls", option);
        // for (unsigned i = 1; i < size; i++){
        //     if (strcmp(arguments[i], "-l")){
        //         if (params->getOutputRedirect() != NULL){
        //             //write directory contents to file

        //         } else {
        //             //write directory contents to cout
        //         }
        //     }
        // }
    } else if (strcmp(arguments[0], "grep") == 0){
        //write # of lines with given word to cout
        for (unsigned i = 1; i < size; i++){
            if (strcmp(arguments[i], "-i")){
                //do something
            }
        }
    } else if (strcmp(arguments[0], "cat") == 0){
        // displays the source code of the program on the screen
        if (params->getInputRedirect() != NULL){
            if (params->getBackground() == 0){
                //displays the source code of the program on the screen
            } else {
                // as above except the output will be displayed in the background causing
                //     the prompt of the shell to be mixed with the output of the file
            }
        } else {
            if (params->getBackground() == 1){
                //displays the content of the text file testfile.txt on the screen in the
                    // background
            }
        }
        
    } else if (strcmp(arguments[0], "./slow") == 0){
        if (params->getBackground()){
            // execv()
            // runs the program slow from the current working directory in the background
        }
    } else {
        //Error message
    }
}

int main(int argC, char **argV){
    Shell shell = Shell(argC, argV);
    shell.run();

    return 0;
}