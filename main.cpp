#include <iostream>
#include "myshell.hpp"

int main(int argC, char **argV){
    Shell shell = Shell(argC, argV);
    shell.run();

    return 0;
}