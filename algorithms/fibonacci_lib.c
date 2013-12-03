#include <stdio.h>

#include "fibonacci_lib.h"
#include "common_lib.h"

void fibonacci(int n, int seq[], int last_in_seq)
{
    if(last_in_seq <= n) {
        seq[last_in_seq] = seq[last_in_seq-1] + seq[last_in_seq-2];
        fibonacci(n, seq, last_in_seq+1);
    }
    return;
}
