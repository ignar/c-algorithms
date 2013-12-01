#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "merge_sort_lib.h"

int * shifted_array(int array[], int count)
{
    int * shifted = malloc((count-1) * sizeof(*array));
    for(int i = 0; i < count; i++)
        shifted[i] = array[i+1];
    return shifted;
}

void shift(int a[], size_t nmemb, int dst)
{
    int left = dst < 0;

    dst = abs(dst) % nmemb;

    if(dst)
    {
        int b[dst];

        if(left)
        {
            bcopy(a, b, dst * sizeof(int));
            bcopy(&a[dst], a, (nmemb - dst) * sizeof(int));
            bcopy(b, &a[nmemb - dst], dst * sizeof(int));
        }
        else
        {
            bcopy(&a[nmemb - dst], b, dst * sizeof(int));
            bcopy(a, &a[dst], (nmemb - dst) * sizeof(int));
            bcopy(b, a, dst * sizeof(int));
        }
    }
}

void merge_two_arrays(int a1[], size_t l1, int a2[], size_t l2, int array[])
{
    int *compound = malloc((l1 + l2) * sizeof(*a1));
    int *left = malloc(l1 * sizeof(*a1));
    int *right = malloc(l2 * sizeof(*a2));
    memcpy(left, a1, l1*sizeof(*a1));
    memcpy(right, a2, l2*sizeof(*a2));

    int cnt = (int)(l1 + l2);

    for(int i = 0; i < cnt; i++)
    {
        if(l1 == 0) {
            compound[i] = right[0];
            int *new_right = shifted_array(right, (int)l2);
            free(right);
            right = new_right;
            l2--;
            print_array(compound, cnt);
        } else if (l2 == 0) {
            compound[i] = left[0];
            int *new_left = shifted_array(left, (int)l1);
            free(left);
            left = new_left;
            l1--;
        } else {
            if(left[0] < right[0]) {
                compound[i] = left[0];
                int *new_left  = shifted_array(left, (int)l1);
                free(left);
                left = new_left;
                l1--;
                print_array(compound, cnt);
            } else {
                compound[i] = right[0];
                int *new_right = shifted_array(right, (int)l2);
                free(right);
                right = new_right;
                l2--;
                print_array(compound, cnt);
            }
        }
    }

    memcpy(array, compound, cnt*sizeof(*compound));
    free(compound);
    free(left);
    free(right);
    return;
}

void merge(int a[], int m, int b[], int n, int sorted[]) {
    int i, j, k;

    j = k = 0;

    for (i = 0; i < m + n;) {
        if (j < m && k < n) {
            if (a[j] < b[k]) {
                sorted[i] = a[j];
                j++;
            }
            else {
                sorted[i] = b[k];
                k++;
            }
            i++;
        }
        else if (j == m) {
            for (; i < m + n;) {
                sorted[i] = b[k];
                k++;
                i++;
            }
        }
        else {
            for (; i < m + n;) {
                sorted[i] = a[j];
                j++;
                i++;
            }
        }
    }
}

void split_n_sort(int array[], size_t count)
{
    if(count == 1) return;

    int c2 = (int)count/2;

    if(count == 2) {
        //merge_two_arrays(array, c2, array+c2, c2, array);

        int *t1 = malloc(c2*sizeof(*array));
        memcpy(t1, array, c2*sizeof(*array));
        int *t2 = malloc(c2*sizeof(*array));
        memcpy(t2, array+c2, c2*sizeof(*array));

        merge(t1, c2, t2, c2, array);
    } else {
        if(count % 2) {
            split_n_sort(array, c2+1);
            split_n_sort(array+c2+1, c2);

            //merge_two_arrays(array, c2+1, array+c2+1, c2, array);
            int *t1 = malloc((c2+1)*sizeof(*array));
            memcpy(t1, array, (c2+1)*sizeof(*array));
            int *t2 = malloc(c2*sizeof(*array));
            memcpy(t2, array+c2+1, c2*sizeof(*array));

            merge(t1, c2+1, t2, c2, array);
        } else {
            split_n_sort(array, c2);
            split_n_sort(array+c2, c2);

            //merge_two_arrays(array, c2, array+c2, c2, array);
            int *t1 = malloc(c2*sizeof(*array));
            memcpy(t1, array, c2*sizeof(*array));
            int *t2 = malloc(c2*sizeof(*array));
            memcpy(t2, array+c2, c2*sizeof(*array));

            merge(t1, c2, t2, c2, array);
        }
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
