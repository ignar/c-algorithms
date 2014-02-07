#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "common_lib.h"

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

char ** split_string(const char *string, const char *delim, size_t *len)
{
    int n_spaces = 0;
    char **res = NULL;
    char *str = malloc(strlen(string));
    memcpy(str, string, strlen(string));

    char *part = strtok(str, delim);
    while(part) {
        res = realloc(res, sizeof(char*) * n_spaces);
        res[n_spaces] = part;
        n_spaces++;
        part = strtok(NULL, delim);
    }
    *len = n_spaces;
    free(str);
    return res;
}

size_t trimwhitespace(char *out, const char *str)
{
    size_t len = strlen(str);
    const char *end;

    while(isspace(*str)) str++;

    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;
    end++;

    size_t out_size;
    out_size = (end - str) < len ? (end - str) : len;

    memcpy(out, str, out_size);
    out[out_size] = 0;
    return out_size;
}
