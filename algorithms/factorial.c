#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "factorial_lib.h"

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Usage:\n> factorial N\n\nWhere N >= 0\n");
        return 1;
    }
    char n = *argv[1];
    if(!isdigit(n)) {
        printf("'%c' is not a number\n", n);
        return 1;
    }
    if(atoi(argv[1]) < 0) {
        printf("Number have to be greater or equal to 0\n");
        return 1;
    }
    unsigned int num = factorial(atoi(argv[1]));
    printf("%d\n", num);
    return 0;
}
