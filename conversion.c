/////
// Name: Yug Vashisth, STD# 400510750
// Conversion
//purpose is to handle conversionn of long to base, and numbers as welll
//uses other imported files to run smoothly
/////


#include <stdio.h>
#include "conversion.h"//include statements 

void conversion(long i, int base) { //initiates conversion, with parameters of long and inteher, converts long to base
    if (i < base) {
        putchar((i < 10) ? '0' + i : 'A' + (i - 10));  // For numbers 0-9, output '0' + i
    } else {
        conversion(i / base, base);
        putchar((i % base < 10) ? '0' + (i % base) : 'A' + ((i % base) - 10));
    }
}

void convert_num(long i, int base){ //same, but converts a number instead
    if (i < 0) { //handles negative values entered
        putchar('-');
        i = -i;
    }
    conversion(i, base); //conversion occurs
    putchar('\n');
}

