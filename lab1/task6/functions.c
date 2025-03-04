#include "functions.h"

status string_to_double(const char *str, double *result) {
    if(!result || !str) return INPUT_ERROR;
    char *endptr;
    *result = strtod(str, &endptr);

    // printf("endptr: %s, result: %lf, str: %s\n", endptr, *result, str);

    if (*endptr != '\0' || endptr == str) {
        return INPUT_ERROR;
    }

    if (*result == HUGE_VAL || *result == -HUGE_VAL) {
        return OVERFLOW_ERROR;
    }

    return OK;
}

double f_a(double x) {
    return log(1 + x) / x;
}

double f_b(double x) {
    return exp(-x * x / 2);
}

double f_c(double x) {
    return log(1 / (1 - x));
}

double f_d(double x) {
    return pow(x, x);
}

// Параметр n определяет количество прямоугольников, на которое делится интервал.
// Вычисляется ширина каждого прямоугольника h = 1.0 / n.
status right_rect(int n, double *result, double (*function)(double)) {
    if (!result || !function) return MEMORY_ERROR;

    double h = 1.0 / n, sum = 0;

    for (int i = 1; i <= n; i++) {
        sum += function((double)i * h);
    }

    *result = sum * h;

    return OK;
}

status left_rect(int n, double *result, double (*function)(double)) {
    if (!result || !function) return MEMORY_ERROR;

    double h = 1.0 / n, sum = 0;

    for (int i = 0; i < n; i++) {
        sum += function((double)i * h);
    }

    *result = sum * h;

    return OK;
}

status integral(double eps, double *result, double (*function)(double), status (*method)(int, double *, double (*)(double))) {
    if (!result || !function || !method) return MEMORY_ERROR;
    double prev = 0.0, cur = 0.0, n = 1;

    do {
        if (INT_MAX / 2 < n) return INPUT_ERROR;
        n *= 2;
        prev = cur;
        if(method(n, &cur, function) != OK) return MEMORY_ERROR;
    } while (fabs(prev - cur) >= eps);

    *result = cur;

    return OK;
}