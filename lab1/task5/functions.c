#include "functions.h"

status string_to_double(const char *str, double *result) {
    if(!result || !str) return INPUT_ERROR;
    char *endptr;
    *result = strtod    (str, &endptr);

    // printf("endptr: %s, result: %lf, str: %s\n", endptr, *result, str);

    if (*endptr != '\0' || endptr == str) {
        return INPUT_ERROR;
    }

    if (*result == HUGE_VAL || *result == -HUGE_VAL) {
        return OVERFLOW_ERROR;
    }

    return OK;
}

status sum_a(double x, double eps, double *result) {
    if(!result) return INPUT_ERROR;
    int n = 0;
    *result = 0;
    double cur = 1;
    while (fabs(cur) >= eps) {
        (*result) += cur;
        if (n == INT_MAX)
            return INPUT_ERROR;
        n++;
        cur *= x / n;
    }
    return OK;
}

status sum_b(double x, double eps, double *result) {
    if(!result) return INPUT_ERROR;
    int n = 0;
    *result = 0;
    double cur = 1;
    while (fabs(cur) >= eps) {
        (*result) += cur;
        if (n == INT_MAX)
            return INPUT_ERROR;
        n++;
        cur *= (-1.0) * x * x / (2 * n * (2 * n - 1.0));
    }
    return OK;
}

status sum_c(double x, double eps, double *result) {
    if(!result) return INPUT_ERROR;
    if(fabs(x) >= 1.0 - __DBL_EPSILON__) return ROW_DIVERGES;
    int n = 0;
    *result = 0;
    double cur = 1;
    while (fabs(cur) >= eps) {
        (*result) += cur;
        if (n == INT_MAX)
            return INPUT_ERROR;
        n++;
        cur *= (x * x * 9.0 * n * n) / (9 * n * (n - 1) + 2);
    }
    return OK;
}

status sum_d(double x, double eps, double *result) {
    if(!result) return INPUT_ERROR;
    if(fabs(x) > 1.L) return ROW_DIVERGES;
    int n = 1;
    *result = 0;
    double cur = -1.0 * x * x / 2.0;
    while (fabs(cur) >= eps) {
        (*result) += cur;
        // if(n % 10000000 == 0) printf("n: %d, cur: %lf ", n, cur);
        n++;
        cur *= (-1 * (2 * n - 1)  * x * x ) / (2 * n);
    }
    return OK;
}