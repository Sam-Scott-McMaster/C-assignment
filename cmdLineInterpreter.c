#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversion.h"
#include "cmdLineInterpreter.h"

void cmdLineInterpreter(int argc, char *argv[]) {
    int base = 16;        
    long start = 0, finish = 0;
    int rangeFlag = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0) {
            if (i + 1 < argc) {
                base = atoi(argv[i + 1]); 
                if (base < 2 || base > 36) {
                    fprintf(stderr, "Usage: convert [-b BASE] [-r START FINISH]\n1 < BASE < 37\n");
                    fprintf(stderr, "START and FINISH are long integers\n" );
                    exit(1);
                }
                i++;
            } else {
                fprintf(stderr, "Error: No base specified after -b\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "-r") == 0) {
            if (i + 2 < argc) {
                start = atol(argv[i + 1]);  
                finish = atol(argv[i + 2]); 
                rangeFlag = 1;
                i += 2; 
            } else {
                fprintf(stderr, "Error: No range specified after -r\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "--help") == 0) {
            printf(" WELCOME TO THE HELP PORTAL \n");
            printf("A utility for converting numbers between bases.\nOptions:\n");
            fprintf(stderr, 
                "Usage: convert [OPTIONS] [NUMBER]\n\n"
                "A utility for converting numbers between bases.\n\n"
                "Options:\n"
                "  -b BASE          Set the base for conversion (2 to 36).\n"
                "                   Default is base 10.\n"
                "  -r START FINISH  Convert numbers in the range from START to FINISH (inclusive).\n"
                "                   Outputs each converted number on a new line.\n"
                "  --help           Display this help message and exit.\n\n"
                "Input:\n"
                "  If no range (-r) is specified, the program reads integers from standard input\n"
                "  until EOF is encountered. Converted output is displayed immediately.\n\n"
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
            fprintf(stderr, "Error: unknown input, please re-run program and try again %s\n", argv[i]);
            exit(1);
        }
    }

    if (rangeFlag) {
        for (long i = start; i <= finish; i++) {
            convert_num(i, base);
        }
    } else {
        long num;
        while (1) {
            int result = scanf("%ld", &num);
            switch (result) {
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

