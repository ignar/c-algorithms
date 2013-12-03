#include "factorial_lib.h"

unsigned int factorial(int n)
{
    unsigned int f;
    if(n == 0) {
        f = 1;
    } else {
        f = n * factorial(n-1);
    }
    return f;
}
