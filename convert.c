#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void conversion(long i, int base) {
    if (i < base) {
        putchar((i < 10) ? '0' + i : 'A' + (i - 10));
    } else {
        conversion(i / base, base);
        putchar((i % base < 10) ? '0' + (i % base) : 'A' + ((i % base) - 10));
    }
}

void convert_num(long i, int base){
    if (i<0){
        putchar('-');
        i = -i;
    }
    conversion(i,base);
    putchar('\n');
}

void cmdLineInterpreter(int argc, char *argv[]) {
    int base = 16;         // Default base
    long start = 0, finish = 0;
    int rangeFlag = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0) {
            if (i + 1 < argc) {
                base = atoi(argv[i + 1]); // Convert base from string to int
                if (base < 2 || base > 36) {
                    fprintf(stderr, "Usage: convert [-b BASE] [-r START FINISH]\n1 < BASE < 37\n");
                    fprintf(stderr, "START and FINISH are long integers\n" );
                    exit(1);
                }
                i++; // Skip the next argument, as it's been processed
            } else {
                fprintf(stderr, "Error: No base specified after -b\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "-r") == 0) {
            if (i + 2 < argc) {
                start = atol(argv[i + 1]);  // Convert start from string to long
                finish = atol(argv[i + 2]); // Convert finish from string to long
                rangeFlag = 1;
                i += 2; // Skip the next two arguments, as they've been processed
            } else {
                fprintf(stderr, "Error: No range specified after -r\n");
                exit(1);
            }
        }    
        else if (strcmp(argv[i], "--help") == 0) {
            printf("WRITE A GOOD HELP MESSAGE\n");
            exit(0);
        } else {
            fprintf(stderr, "Error: unknown input, please re-run program and try again %s\n", argv[i]);
            exit(1);
        }
    }

    // Call the convert function with the parsed base and range values
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
                // Process the valid integer input
                convert_num(num, base);
                break;
            default:
                fprintf(stderr, "Error: Non-long-int token encountered.\n");
                exit(1);
        }}

       
    }
}

int main(int argc, char *argv[]) {
    cmdLineInterpreter(argc, argv);
    return 0;
}