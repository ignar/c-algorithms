#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "fibonacci_lib.h"
#include "common_lib.h"

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Usage:\n> fibonacci N\n\nWhere N >= 0\n");
        return 1;
    }

    char *cn = argv[1];
    if(!isdigit(*cn)) {
        printf("'%c' is not a number\n", *cn);
        return 1;
    }

    int n = atoi(cn);
    if(n < 0) {
        printf("Number have to be greater or equal to 0\n");
        return 1;
    }

    int seq[n];
    seq[0] = 0;
    seq[1] = 1;
    fibonacci(n, seq, 2);

    print_array(seq, n);
    return 0;
}
