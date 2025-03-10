#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define EPS DBL_EPSILON

typedef enum Status
{
    OK,
    INPUT_ERROR,
    BASE_ERROR,
    MEMORY_ERROR
} status;

status has_a_finite_representation(double eps,int base, double *res, int *len_ans, int count_nums, ...);
int _has_representation(double eps, int base, double num);
unsigned long long gcd(unsigned long long a, unsigned long long b);


#endif