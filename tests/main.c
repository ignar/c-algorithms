#include "minunit.h"
#include <ncurses.h>

#include "closest_pair_lib_test.c"
#include "common_lib_test.c"
#include "merge_sort_test.c"

int tests_run = 0;

static char * all_tests()
{
    // merge_sort
    mu_run_test(test_merge_array_with_two_elements);
    mu_run_test(test_merge_array_with_three_elements);
    mu_run_test(test_merge_array_with_four_elements);
    mu_run_test(test_split_n_sort_one_elements);
    mu_run_test(test_split_n_sort_two_elements);
    mu_run_test(test_split_n_sort_three_elements);
    mu_run_test(test_split_n_sort_four_elements);
    mu_run_test(test_shift_left);
    mu_run_test(test_shift_right);

    // common_lib
    mu_run_test(test_split_string);
    mu_run_test(test_trimwhitespace1);
    mu_run_test(test_trimwhitespace2);
    mu_run_test(test_trimwhitespace3);

    // closest_pair
    mu_run_test(test_closes_with_3_elem_x);
    mu_run_test(test_closes_with_3_elem_y);
    //mu_run_test(test_closes_with_more_when_3_elem_x);
    //mu_run_test(test_closes_with_more_when_3_elem);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
