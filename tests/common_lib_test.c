#include <stdio.h>
#include <string.h>
#include "../algorithms/common_lib.c"

char * test_split_string()
{
    char str[] = "41,27";
    char delim[] = ",";
    size_t len = 0;
    char **result = split_string(str, delim, &len);
    mu_assert("len is not 2", len == 2);
    mu_assert("1: _1_,2 => [_1_, 2]", strcmp("41", result[0]) == 0);
    mu_assert("2: 1,_2_ => [1, _2_]", strcmp("27", result[1]) == 0);
    free(result);
    return 0;
}

char * test_trimwhitespace1()
{
    char str[] = "  dt  ";
    char out[20];
    size_t size = trimwhitespace(out, str);
    mu_assert("1: size != 2", size == 2);
    mu_assert("1: after trim str != dt", strcmp(out, "dt") == 0);
    return 0;
}


char * test_trimwhitespace2()
{
    char str[] = "dt";
    char out[40];
    trimwhitespace(out, str);
    mu_assert("2: after trim str != dt", strcmp(out, "dt") == 0);
    return 0;
}

char * test_trimwhitespace3()
{
    char str[] = "  dt";
    char out[40];
    trimwhitespace(out, str);
    mu_assert("3: after trim str != dt", strcmp(out, "dt") == 0);
    return 0;
}
