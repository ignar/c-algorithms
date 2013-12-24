#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "common_lib.h"
#include "merge_sort_lib.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Give me the initial array\n");
        return 1;
    }

    int *unsorted_array = malloc((argc-1)*sizeof(int));

    for(int i = 1, j = 0; i < argc; i++, j++)
    {
        unsorted_array[j] = (int) atoi(argv[i]);
    }

    size_t len_of_unsorted_array = argc-1;
    split_n_sort(unsorted_array, len_of_unsorted_array);

    print_array(unsorted_array, len_of_unsorted_array);

    free(unsorted_array);
    return 0;
}
