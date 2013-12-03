#include <stdlib.h>
#include <stdio.h>

void print_array(int array[], size_t count)
{
    printf("(");
    for(size_t i = 0; i < count; i++) {
        printf("%d", array[i]);
        if(i+1 < count) {
            printf(", ");
        }
    }
    printf(")\n");
    return;
}
