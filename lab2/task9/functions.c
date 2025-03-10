#include "functions.h"

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (a > 0 && b > 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return (a > 0) ? a : b;
}

int _has_representation(double eps, int base, double num) {
    if (base < 2 || num < -eps || num >= 1.0 || eps < DBL_EPSILON) return 0;
    unsigned long long numerator, denominator = 1;
    int i;
    double temp = num;
    while (fabs(num - floor(num)) > eps && ULLONG_MAX / 10 >= denominator) {
        temp *= 10;
        denominator *= 10;
    }
    numerator = ((unsigned long long)temp);
    unsigned long long deviser = gcd(numerator, denominator);

    numerator /= deviser;
    denominator /= deviser;

    printf("Start num: %lf, numerator: %llu, denominator: %llu\n", num, numerator, denominator);

    if (denominator % 2 == 0) {
        if (base % 2 != 0) {
            return 0; // В base нет делителя 2
        }
        // Удаляем все множители 2 из denominator
        while (denominator % 2 == 0) {
            denominator /= 2;
        }
    }

    for (i = 3; i <= base; i += 2) {
        if (denominator % i == 0 && (base % i) != 0)
            return 0;
        while (denominator % i == 0)
            denominator /= i;
    }
    /*Если после всех проверок знаменатель не равен 1, это значит,
     что остались множители, которые не входят в основание системы счисления, 
     и число не может быть представлено.*/
    if (denominator != 1)
        return 0;
    return 1;
}

status has_a_finite_representation(double eps, int base, double *res, int *len_ans, int count_nums, ...) {
    if(!res || !len_ans || (base < 2))
        return INPUT_ERROR;
 
    *len_ans = 0;

    int i;
    status state = OK;
    double number;
    va_list args;
    va_start(args, count_nums);
    *len_ans = 0;

    for (i = 0; i < count_nums; ++i) {
        number = va_arg(args, double);
        if (number > 1.0 - eps || number < -eps) {
            va_end(args);   
            return INPUT_ERROR;
        }
        if (_has_representation(eps, base, number)) {
            res[(*len_ans)++] = number;
        }
    }

    va_end(args);
    return OK;
}