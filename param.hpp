/***************************************************************
  Student Name: Ari Palanjian
  File Name: param.hpp
  Project 1

  Param class definition
    Class to hold input data
***************************************************************/
#ifndef PARAM_HPP
#define PARAM_HPP
#define MAXARGS 32
class Param{
    char *inputRedirect; /* file name or NULL */
    char *outputRedirect; /* file name or NULL */
    int background; /* either 0 (false) or 1 (true) */
    int argumentCount; /* number of tokens in argument vector */
    char *argumentVector[MAXARGS]; /* array of strings */
public:
    Param();
    ~Param(){}
    char* getInputRedirect();
    char* getOutputRedirect();
    int getBackground();
    int getArgumentCount();
    char** getArgumentVector();
    void setInputRedirect(char* input);
    void setOutputRedirect(char* output);
    void setBackground(int background);
    void setArgumentCount(int count);
    void setArgumentVector(char** arguments);
    void printParams();
    void resetParams();
};

#endif