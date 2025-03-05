#include "functions.h"

int main(int argc, char *argv[])
{
    double result;

    puts("\n\ttest 1\nx - 11.2232, eps = 1e-10\nexpected result: 11.2232");
    switch (bisection_method(&result, 11., 11.5, 1.e-10, func1))
    {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case OK:
        printf("\t result: %lf\n", result);
        break;
    }

    puts("\n\ttest 2\nx - 11.2232, eps = 0.01\nexpected result: 11.22(...)");
    switch (bisection_method(&result, 11., 11.5, 0.01, func1))
    {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case OK:
        printf("\t result: %lf\n", result);
        break;
    }

    puts("\n\ttest 3\nsin(x)-1/x, eps = 1e-10\nexpected result: 1.114157");
    switch (bisection_method(&result, 1., 2.5, 1.e-10, func2))
    {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case OK:
        printf("\t result: %lf\n", result);
        break;
    }

    puts("\n\ttest 4\nx^2 + 10x - 4, eps = 1e-10\nexpected result: -10.385165");
    switch (bisection_method(&result, -10., -12.5, 1.e-10, func3))
    {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case OK:
        printf("\t result: %lf\n", result);
        break;
    }

    puts("\n\ttest 5\n3x^3 + x^2 + x + 1, eps = 1e-10\nexpected result: -0.635024");
    switch (bisection_method(&result, -2., 2., 1.e-10, func4))
    {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case OK:
        printf("\t result: %lf\n", result);
        break;
    }

    puts("\n\ttest 6\nsqrt(x) - 4.4, eps = 1e-10\nexpected result: 19.36");
    switch (bisection_method(&result, 0., 20., 1.e-10, func5))
    {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case OK:
        printf("\t result: %lf\n", result);
        break;
    }

    puts("\n\ttest 6\nsqrt(x) - 4.4, eps = 1e-10\nexpected result: no roots in this interval");
    switch (bisection_method(&result, 0., 19.35, 1.e-10, func5))
    {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case OK:
        printf("\t result: %lf\n", result);
        break;
    }

    puts("\n\ttest 6\nsqrt(x) - 4.4, eps = -1e-10\nexpected result: Input error");
    switch (bisection_method(&result, 0., 20., -1.e-10, func5))
    {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case OK:
        printf("\t result: %lf\n", result);
        break;
    }

    // puts("\n\ttest 1\n2x - 5 = 0, eps = 1e-10\nexpected result: 2.5");
    // switch (bisection_method(&result, 1., 3., 1e-10, func1)) {
    // case INPUT_ERROR:
    //     puts("Input error\n");
    //     return INPUT_ERROR;
    // case NO_ROOTS:
    //     puts("No roots in this interval\n");
    //     break;
    // case OK:
    //     printf("\t result: %.16lf\n", result);
    //     break;
    // }

    // puts("\n\ttest 2\nexp(x) - 2 = 0, eps = 1e-10\nexpected result: ~0.693147");
    // switch (bisection_method(&result, 0., 1., 1e-10, func2)) {
    // case INPUT_ERROR:
    //     puts("Input error\n");
    //     return INPUT_ERROR;
    // case NO_ROOTS:
    //     puts("No roots in this interval\n");
    //     break;
    // case OK:
    //     printf("\t result: %.10lf\n", result);
    //     break;
    // }

    // puts("\n\ttest 3\nln(x) - 1 = 0, eps = 1e-10\nexpected result: ~2.718281");
    // switch (bisection_method(&result, 2., 3., 1e-10, func3)) {
    // case INPUT_ERROR:
    //     puts("Input error\n");
    //     return INPUT_ERROR;
    // case NO_ROOTS:
    //     puts("No roots in this interval\n");
    //     break;
    // case OK:
    //     printf("\t result: %.10lf\n", result);
    //     break;
    // }

    // puts("\n\ttest 4\nx^2 - 3x + 2 = 0, eps = 1e-10\nexpected result: 1.0");
    // switch (bisection_method(&result, 0.5, 1.5, 1e-10, func4)) {
    // case INPUT_ERROR:
    //     puts("Input error\n");
    //     return INPUT_ERROR;
    // case NO_ROOTS:
    //     puts("No roots in this interval\n");
    //     break;
    // case OK:
    //     printf("\t result: %.10lf\n", result);
    //     break;
    // }

    // puts("\n\ttest 5\ncos(x) = 0, eps = 1e-10\nexpected result: ~1.570796");
    // switch (bisection_method(&result, 1., 2., 1e-10, func5)) {
    // case INPUT_ERROR:
    //     puts("Input error\n");
    //     return INPUT_ERROR;
    // case NO_ROOTS:
    //     puts("No roots in this interval\n");
    //     break;
    // case OK:
    //     printf("\t result: %.10lf\n", result);
    //     break;
    // }

    return 0;
}