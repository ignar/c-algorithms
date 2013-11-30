#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort(int array[]);
void split_n_sort(int arr[], size_t count);
void merge_two_arrays(int a1[], size_t l1, int a2[], size_t l2, int array[]);
void print_array(int array[], size_t count);

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

    return 0;
}

int * shifted_array(int array[], int count)
{
    int * shifted = malloc((count-1) * sizeof(*array));
    for(int i = 0; i < count; i++)
        shifted[i] = array[i+1];
    return shifted;
}

void merge_two_arrays(int a1[], size_t l1, int a2[], size_t l2, int array[])
{
    int *compound = malloc((l1 + l2) * sizeof(*a1));
    int *left = malloc(l1 * sizeof(*a1));
    int *right = malloc(l2 * sizeof(*a2));
    memcpy(left, a1, l1*sizeof(*a1));
    memcpy(right, a2, l2*sizeof(*a2));

    int cnt = l1 + l2;

    for(size_t i = 0; i < cnt; i++)
    {
        if(l1 == 0) {
            compound[i] = right[0];
            right = shifted_array(right, l2);
            l2--;
        } else if (l2 == 0) {
            compound[i] = left[0];
            left = shifted_array(left, l1);
            l1--;
        } else {
            if(left[0] < right[0]) {
                compound[i] = left[0];
                left = shifted_array(left, l1);
                l1--;
            } else {
                compound[i] = right[0];
                right = shifted_array(right, l2);
                l2--;
            }
        }
    }

    memcpy(array, compound, cnt*sizeof(*compound));
    return;
}

void split_n_sort(int array[], size_t count)
{
    int c2 = count/2;
    if(c2 == 1){
        merge_two_arrays(array, c2, array+c2, c2, array);
    } else {
        split_n_sort(array, c2);
        split_n_sort(array+c2, c2);
        merge_two_arrays(array, c2, array+c2, c2, array);
    }
    return;
}

void print_array(int array[], size_t count)
{
    printf("(");
    for(size_t i = 0; i < count; i++)
    {
        printf("%d", array[i]);
        if(i+1 < count) {
            printf(", ");
        }
    }
    printf(")\n");
    return;
}
