#include "functions.h"

status string_to_int(const char *str, long *result) {
    if(!result || !str) return INPUT_ERROR;
    char *endptr;
    *result = strtol(str, &endptr, 10);

    // printf("endptr: %s, result: %lf, str: %s\n", endptr, *result, str);

    if (*endptr != '\0' || endptr == str) {
        return INPUT_ERROR;
    }

    if (*result == LONG_MAX || *result == LONG_MIN) {
        return INPUT_ERROR;
    }

    return OK;
}

// status string_to_int(const char *str, long *result) {
//     if (!str || !result) return MEMORY_ERROR;

//     char *endinp;

//     for (int i = 0; i < strlen(str); i++) {
//         if ((str[i] < '0' || str[i] > '9') && !(str[i] == '-' && i == 0)) return INPUT_ERROR;
//     }

//     *result = strtol(str, &endinp, 10);

//     if (*result == LONG_MAX || *result == LONG_MIN) return INPUT_ERROR;

//     if (*endinp != '\0') return INPUT_ERROR;

//     return OK;
// }

status generate_static_array(long array[], long a, long b) {
    if(!array) return MEMORY_ERROR;
    srand(time(NULL));
    for (int i = 0; i < CAPACITY; i++) {
        array[i] = a + (rand() % (b - a + 1));
    }
    return OK;
}

status swap_min_max(long array[]) {
    if(!array) return MEMORY_ERROR;
    int i_max = 0, i_min = 0;
    long temp;

    for (int i = 0; i < CAPACITY; i++) {
        if (array[i] > array[i_max]) i_max = i;
        if (array[i] < array[i_min]) i_min = i;
    }

    array[i_max] = array[i_max] ^ array[i_min];
    array[i_min] = array[i_max] ^ array[i_min];
    array[i_max] = array[i_max] ^ array[i_min];
    return OK;
}

status generate_dynamic_array(int **array, int size_array) {
    if (!array) return MEMORY_ERROR;

    srand(time(NULL));
    *array = malloc(size_array * sizeof(int));

    if (*array == NULL) return MEMORY_ERROR;

    for (int i = 0; i < size_array; i++) {
        (*array)[i] = rand() % 2001 - 1000;
    }

    return OK;
}

status bubble_sort(int *array, int size_array) {
    if (!array) return MEMORY_ERROR;

    long temp;

    for (int i = 0; i < size_array; i++) {
        for (int j = 0; j < size_array - i - 1; j++) {
            if (array[j + 1] < array[j]) {
                array[j] = array[j] ^ array[j + 1];
                array[j + 1] = array[j] ^ array[j + 1]; 
                array[j] = array[j] ^ array[j + 1];
            }
        }
    }

    return OK;
}

status find_nearest_num(int x, int *array, int size_array, int *res) {
    if (!array) return MEMORY_ERROR;

    int l = 0, r = size_array - 1, mid;

    while (l <= r) {
        mid = (l + r) / 2;
        if (array[mid] > x) r = mid - 1;
        else l = mid + 1;
    }

    if (r < 0) {
        *res = array[l];
        return OK;
    }
    if (l >= size_array) {
        *res = array[r];
        return OK;
    }

    *res = ((abs(array[l] - x) < abs(array[r] - x)) ? array[l] : array[r]);
    return OK;
}

status generate_sum_array(int *A, int *B, int *C, int size_array) {
    if (!A || !B || !C) return MEMORY_ERROR;
    bubble_sort(B, size_array);
    int fnm;

    for (int i = 0; i < size_array; i++) {
        if (find_nearest_num(A[i], B, size_array, &fnm) != OK) return MEMORY_ERROR;
        C[i] = A[i] + fnm;
    }

    return OK;
}