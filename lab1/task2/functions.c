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

status e_limit(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    int n = 1;
    double cur = 0, prev = 0;
    
    do {
        prev = cur;
        cur = pow((1.0 + 1.0 / n), n);
        n *= 2;
    } while (fabs(prev - cur) >= eps);

    *result = cur;
    return OK;
}

status pi_limit(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    int n = 2;
    double cur = 4, prev = 0;

    do {
        prev = cur;
        cur *= (4.0 * n * (n - 1.0)) / pow(2.0 * n - 1.0, 2);
        n++;
    } while (fabs(prev - cur) >= eps);

    *result = cur;
    return OK;
}

status ln2_limit(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    int n = 1;
    double cur = 0, prev = 0;

    do {
        prev = cur;
        cur = n * (pow(2, 1.0 / (double)n) - 1);
        n *= 2;
    } while (fabs(prev - cur) >= eps);

    *result = cur;
    return OK;
}

status sqrt_limit(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    int n = 1;
    double cur = -0.5, prev = -0.5;

    do {
        prev = cur;
        cur = prev - prev * prev / 2 + 1;
        n++;
    } while (fabs(prev - cur) >= eps);

    *result = cur;
    return OK;
}

double sum(int n) { //sum(1/k), k->n
    double s = 0;

    for (int k = 1; k <= n; k++) {
        s += (1.0 / k);
    }

    return s;
}

status y_limit(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    int n = 1;
    double cur = 1, prev = 1;

    do {
        prev = cur;
        n *= 2;
        cur = sum(n) - log(n);
    } while (fabs(prev - cur) >= eps);

    *result = cur;
    return OK;
}

status e_row(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    double sum = 1, prev = 1;
    int n = 1;

    do {
        prev /= (double)n;
        sum += prev;
        n++;
    } while (prev >= eps);

    *result = sum;
    return OK;
}

status pi_row(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    double sum = 0, cur = 0, sign = 1;
    int n = 1;

    do {
        cur = sign / (2.0 * n - 1.0);
        sum += cur;
        n++;
        sign *= -1;
    } while (fabs(4 * cur) >= eps);

    *result = 4.0 * sum;
    return OK;
}

status ln2_row(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    double sum = 0, cur = 0, sign = 1;
    int n = 1;

    do {
        cur = sign / n;
        sum += cur;
        n++;
        sign *= -1;
    } while (fabs(cur) >= eps);

    *result = sum;
    return OK;
}

status sqrt_row(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    double prod, cur = pow(2.0, 0.25), prev_prod; // k=2
    prod = cur;

    do {
        prev_prod = prod;
        cur = pow(cur, 0.5);
        prod *= cur;
    } while (fabs(prev_prod - prod) >= eps);

    *result = prod;
    return OK;
}

status y_row(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    double previous = 0;
    double current = 0.5;
    int k = 2;
    double l = 0;

    do {
        previous = current;
        k++;
        l = sqrt(k);
        if (fmod(l, 1.0) < DBL_EPSILON) {
            k++;
            l = (int)sqrt(k);
        }
        current += 1.0 / pow((int)l, 2.0) - 1.0 / k;

    } while (fabs(previous - current) >= eps);

    *result = (current - pow(PI, 2) / 6);
    return OK;
}

status e_equation(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;
    double x = 3, f = 1, df, last_x = 0;
    while (fabs(last_x - x) >= eps) {
        f = log(x) - 1;
        df = 1.0 / x;
        last_x = x;
        x = x - f / df;
    }
    *result = x;
    return OK;
}

status pi_equation(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;
    double x = 3, f = 1, df, last_x = 0;
    while (fabs(last_x - x) >= eps) {
        f = cos(x) + 1;
        df = -sin(x);
        last_x = x;
        x = x - f / df;
    }
    *result = x;
    return OK;
}

status ln2_equation(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;
    double x = 1, f = 1, df, last_x = 0;
    while (fabs(last_x - x) >= eps) {
        f = exp(x) - 2;
        df = exp(x);
        last_x = x;
        x = x - f / df;
    }
    *result = x;
    return OK;
}

status sqrt_equation(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;
    double x = 1, f = 1, df, last_x = 0;
    while (fabs(last_x - x) >= eps) {
        f = x * x - 2;
        df = 2 * x;
        last_x = x;
        x = x - f / df;
    }
    *result = x;
    return OK;
}

int is_prime(int number) {
    if (number <= 1 || number % 2 == 0) return 0;
    if (number == 2) return 1;

    for (int i = 3; i * i <= number; i += 2) {
        if (number % i == 0) return 0;
    }

    return 1;
}

status y_equation(double eps, double *result) {
    if(!result || eps < DBL_EPSILON) return INPUT_ERROR;

    int p = 2;
    double cur = log(2) * 0.5, prev = 0, prod = 0.5;

    do {
        prev = cur;

        do {
            p++;
        } while (!is_prime(p));

        prod *= (p - 1.0) / p;
        cur = log(p) * prod;

    } while (fabs(prev - cur) >= eps);

    *result = (-log(cur));
    return OK;
}