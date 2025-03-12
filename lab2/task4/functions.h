#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "stdio.h"
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

#define CAPACITY 128

typedef enum Status {
    OK,
    INPUT_ERROR,
    MEMORY_ERROR,
    OVERFLOW_ERROR
} status;

typedef struct Point {
    double x;
    double y;
} point;

int is_convex(int count_corners, ...);
status find_polynom(double *res, double x, int n, ...);
status is_kaprekar(int count_numbers, char *ans, int base, ...);

#endif