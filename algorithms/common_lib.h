#include <stdlib.h>

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define ABS(a)     (((a) < 0) ? -(a) : (a))

void print_array(int array[], size_t count);
char ** split_string(const char *string, const char *delim, size_t *len);
size_t trimwhitespace(char *out, const char *str);
