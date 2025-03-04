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
    OVERFLOW_ERROR
} status;

status string_to_double(const char *str, double *result);
double f_a(double x);
double f_b(double x);
double f_c(double x);
double f_d(double x);
status right_rect(int n, double *result, double (*function)(double));
status left_rect(int n, double *result, double (*function)(double));
status integral(double eps, double *result, double (*function)(double), status (*method)(int, double *, double (*)(double)));


#endif