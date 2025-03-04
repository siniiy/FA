#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define CAPACITY 10

typedef enum Status {
    OK,
    INPUT_ERROR,
    MEMORY_ERROR
} status;

status string_to_int(const char *str, long *result);
status generate_static_array(long array[], long a, long b);
status swap_min_max(long array[]);
status generate_dynamic_array(int **array, int size_array);
status bubble_sort(int *array, int size_array);
status find_nearest_num(int x, int *array, int size_array, int *res);
status generate_sum_array(int *A, int *B, int *C, int size_array);

#endif