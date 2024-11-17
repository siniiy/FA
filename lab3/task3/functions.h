#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define EPS 1e-10

typedef enum Status {
    OK,
    INP_ERROR,
    FILE_ERROR,
    MEM_ERROR,
} status;

typedef struct Employee {
    unsigned int id;
    char name[32];
    char surname[32];
    double salary;
} Employee;

status inp_validate(int argc, char **argv);
status read_from_file(FILE * input, Employee **data, int *data_size);
int compare_a(const void *a, const void *b);
int compare_d(const void *a, const void *b);

#endif