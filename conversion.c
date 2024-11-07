#include <stdio.h>
#include "conversion.h"

void conversion(long i, int base) {
    if (i < base) {
        putchar((i < 10) ? '0' + i : 'A' + (i - 10));
    } else {
        conversion(i / base, base);
        putchar((i % base < 10) ? '0' + (i % base) : 'A' + ((i % base) - 10));
    }
}

void convert_num(long i, int base){
    if (i < 0) {
        putchar('-');
        i = -i;
    }
    conversion(i, base);
    putchar('\n');
}

