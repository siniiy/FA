#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef enum Status {
    OK,
    INPUT_ERROR,
    MEMORY_ERROR,
    FILE_OPEN_ERROR
} status;

status compare_filepaths(char * file_1, char * file_2, int *res);
status exclude_nums(FILE *in, FILE *out);
status count_letters(FILE *in, FILE *out);
status count_symbols(FILE *in, FILE *out);
status replace_symbols(FILE *in, FILE *out);

#endif