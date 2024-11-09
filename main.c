/////
// Name: Yug Vashisth, STD# 400510750
// MAIN
//purpose is to call cmdlineinterpreter, and put the peice stogether to make the program run fully
//uses other imported files to run smoothly
/////



#include "cmdLineInterpreter.h" //include statements
#include "conversion.h"

int main(int argc, char *argv[]) { 
    cmdLineInterpreter(argc, argv); //interpret command line arguments, to configure program
    return 0; //exit program with return succes
}

