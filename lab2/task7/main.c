#include "functions.h"

int main(int argc, char *argv[])
{
    double result;

    puts("\n\ttest 1\n2x + 5 = 0, eps = 1e-10\nexpected result: -2.5");
    switch (dichotomy_method(&result, -3., 0., 1e-10, func1)) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case SUCCESS:
        printf("\t result: %.10lf\n", result);
        break;
    }

    puts("\n\ttest 2\nexp(x) - 2 = 0, eps = 1e-10\nexpected result: ~0.693147");
    switch (dichotomy_method(&result, 0., 1., 1e-10, func2)) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case SUCCESS:
        printf("\t result: %.10lf\n", result);
        break;
    }

    puts("\n\ttest 3\nln(x) - 1 = 0, eps = 1e-10\nexpected result: ~2.718281");
    switch (dichotomy_method(&result, 2., 3., 1e-10, func3)) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case SUCCESS:
        printf("\t result: %.10lf\n", result);
        break;
    }

    puts("\n\ttest 4\nx^2 - 3x + 2 = 0, eps = 1e-10\nexpected result: 1.0");
    switch (dichotomy_method(&result, 0.5, 1.5, 1e-10, func4)) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case SUCCESS:
        printf("\t result: %.10lf\n", result);
        break;
    }

    puts("\n\ttest 5\ncos(x) = 0, eps = 1e-10\nexpected result: ~1.570796");
    switch (dichotomy_method(&result, 1., 2., 1e-10, func5)) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
    case NO_ROOTS:
        puts("No roots in this interval\n");
        break;
    case SUCCESS:
        printf("\t result: %.10lf\n", result);
        break;
    }

    return 0;
}