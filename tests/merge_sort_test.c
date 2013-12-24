#include <stdio.h>
#include "../algorithms/merge_sort_lib.c"

char * test_merge_array_with_two_elements()
{
    int a1[1], a2[1], sorted[2];
    a1[0] = 4;
    a2[0] = 2;
    merge(a1, 1, a2, 1, sorted);
    mu_assert("sorted[0] != 2", sorted[0] == 2);
    mu_assert("sorted[1] != 4", sorted[1] == 4);
    return 0;
}

char * test_merge_array_with_three_elements()
{
    int sorted[3];
    int a1[] = {1, 3};
    int a2[] = {2};
    merge(a1, 2, a2, 1, sorted);
    mu_assert("sorted[0] != 1", sorted[0] == 1);
    mu_assert("sorted[1] != 2", sorted[1] == 2);
    mu_assert("sorted[2] != 3", sorted[2] == 3);
    return 0;
}

char * test_merge_array_with_four_elements()
{
    int sorted[4];
    int a1[] = {1, 3};
    int a2[] = {2, 4};
    merge(a1, 2, a2, 2, sorted);
    mu_assert("sorted[0] != 1", sorted[0] == 1);
    mu_assert("sorted[1] != 2", sorted[1] == 2);
    mu_assert("sorted[2] != 3", sorted[2] == 3);
    mu_assert("sorted[3] != 4", sorted[3] == 4);
    return 0;
}

char * test_split_n_sort_one_elements()
{
    int a[] = {1};
    split_n_sort(a, 1);
    mu_assert("sorted[0] != 1", a[0] == 1);
    return 0;
}

char * test_split_n_sort_two_elements()
{
    int a[] = {2, 1};
    split_n_sort(a, 2);
    mu_assert("sorted[0] != 1", a[0] == 1);
    mu_assert("sorted[1] != 2", a[1] == 2);
    return 0;
}

char * test_split_n_sort_three_elements()
{
    int a[] = {3, 2, 1};
    split_n_sort(a, 3);
    mu_assert("sorted[0] != 1", a[0] == 1);
    mu_assert("sorted[1] != 2", a[1] == 2);
    mu_assert("sorted[2] != 3", a[2] == 3);
    return 0;
}

char * test_split_n_sort_four_elements()
{
    int a[] = {4, 3, 2, 1};
    split_n_sort(a, 4);
    mu_assert("sorted[0] != 1", a[0] == 1);
    mu_assert("sorted[1] != 2", a[1] == 2);
    mu_assert("sorted[2] != 3", a[2] == 3);
    mu_assert("sorted[3] != 4", a[3] == 4);
    return 0;
}

char * test_shift_left()
{
    int a[] = {1, 2, 3, 4};
    shift(a, 4, -1);
    mu_assert("a[0] != 2", a[0] == 2);
    mu_assert("a[1] != 3", a[1] == 3);
    mu_assert("a[2] != 4", a[2] == 4);
    mu_assert("a[3] != 1", a[3] == 1);
    return 0;
}

char * test_shift_right()
{
    int a[] = {1, 2, 3, 4};
    shift(a, 4, 1);
    mu_assert("a[0] != 4", a[0] == 4);
    mu_assert("a[1] != 1", a[1] == 1);
    mu_assert("a[2] != 2", a[2] == 2);
    mu_assert("a[3] != 3", a[3] == 3);
    return 0;
}
