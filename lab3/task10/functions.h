#ifndef _FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    SUCCESS,
    INPUT_ERROR,
    FILE_OPEN_ERROR,
    MEMORY_ERROR
}status;

status compare_filepaths(char * file_1, char * file_2, int *res);
void print_tree(FILE * input, FILE * output);

#endif