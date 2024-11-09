/////
// Name: Yug Vashisth, STD# 400510750
// cmdLineInterpreter class
//purpose of the clase is to handle command line input, and only do that. It checks the input, and handles output accordingly
//uses other imported files to run smoothly
/////



#include <stdio.h> //All of the include "imports" for the file to work properly
#include <stdlib.h>
#include <string.h>
#include "conversion.h"
#include "cmdLineInterpreter.h"

void cmdLineInterpreter(int argc, char *argv[]) {  //initlazlie comandlineinterpreter, which takes two arguments
    int base = 16;         //set base default 
    long start = 0, finish = 0;  //start and finish
    int rangeFlag = 0;

    for (int i = 1; i < argc; i++) {   
        if (strcmp(argv[i], "-b") == 0) { //if statement which checks if -b is enetered, will act accordingly
            if (i + 1 < argc) {
                base = atoi(argv[i + 1]); 
                if (base < 2 || base > 36) { //if base not within parameters, sends to stderr
                    fprintf(stderr, "Usage: convert [-b BASE] [-r START FINISH]\n1 < BASE < 37\n");
                    fprintf(stderr, "START and FINISH are long integers\n" );
                    exit(1);
                }
                i++;
            } else {
                fprintf(stderr, "Error: No base specified after -b\n"); //if no base is specified
                exit(1);
            }
        } else if (strcmp(argv[i], "-r") == 0) {  //checks if -r is entered
            if (i + 2 < argc) {
                start = atol(argv[i + 1]);  
                finish = atol(argv[i + 2]); 
                rangeFlag = 1;
                i += 2; 
            } else {
                fprintf(stderr, "Error: No range specified after -r\n"); //if no range is specified, send to stderr
                exit(1);
            }
        } else if (strcmp(argv[i], "--help") == 0) { //if help is asked ofr, it sends out a linux like help message
            printf(
                "welcome to the help portal! \n" 
                "Here we convert bases, and numbers between bases\n"
                "Options:\n\n"
                "Usage: convert [OPTIONS] [NUMBER]\n\n"
                "Convert numbers between bases.\n\n"
                "Options:\n"
                "  -b BASE          Base for conversion (2 to 36).\n"
                "                   Default is base 10.\n"
                "  -r START FINISH  Convert numbers in the range from START to FINISH (inclusive).\n"
                "                   Outputs each converted number on a new line.\n"
                "  --help           Display this help message and exit.\n\n"
                "Input:\n"
                "If no range (-r) is specified, the program reads integers from standard input\n"
                "until EOF is encountered. Converted output is displayed immediately.\n\n"
                "Examples:\n"
                "  convert -b 16               Convert standard input numbers to hexadecimal.\n"
                "  convert -b 8 -r 10 20       Convert numbers 10 to 20 to octal.\n"
                "  convert --help              Display this help message and exit.\n\n"
                "Exit Status:\n"
                "  0  Successful execution.\n"
                "  1  An error occurred (e.g., invalid base or argument).\n"
            );
            exit(0);
        } else {
            fprintf(stderr, "Error: Invalid option %s. Use --help for more information.\n", argv[i]); //invalid option entered, sends message
            exit(1);
        }
    }

    if (rangeFlag) { //check rangeflag is set
        for (long i = start; i <= finish; i++) { //iterate from start to finish
            convert_num(i, base); //convert the values
        }
    } else {
        long num;
        while (1) {
            int result = scanf("%ld", &num); //reads long integer
            switch (result) { //use switch case for result handling
                case EOF:
                    exit(0);
                case 1:
                    convert_num(num, base);
                    break;
                default:
                    fprintf(stderr, "Error: Non-long-int token encountered.\n");
                    exit(1);
            }
        }
    }
}

