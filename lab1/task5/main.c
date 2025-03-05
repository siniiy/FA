#include "functions.h"
// проверить где расходятся
int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    double eps, x, result;
    int flag = 0;
    if (string_to_double(argv[1], &eps) != OK || eps <= 0) {
        printf("Input error\n");
        return INPUT_ERROR;
    }
    if (string_to_double(argv[2], &x) != OK) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    switch(sum_a(x, eps, &result)) {
        case INPUT_ERROR: {
            printf("a) Input error\n");
            break;
        }
        case OK: {
            printf("a) %lf\n", result);
        }
    }

    switch(sum_b(x, eps, &result)) {
        case INPUT_ERROR: {
            printf("b) Input error\n");
            break;
        }
        case OK: {
            printf("b) %lf\n", result);
        }
    }

    switch(sum_c(x, eps, &result)) { // 2.9... on x = 0.5
        case INPUT_ERROR: {
            printf("c) Input error\n");
            break;
        }
        case ROW_DIVERGES: {
            printf("c) Diverges\n");
            break;
        }
        case OK: {
            printf("c) %lf\n", result);
        }
    }

    switch(sum_d(x, eps, &result)) { // -0.106... on x = 0.5
        case INPUT_ERROR: {
            printf("d) Input error on\n");
            break;
        }
        case ROW_DIVERGES: {
            printf("d) Diverges\n");
            break;
        }
        case OK: {
            printf("d) %lf\n", result);
        }
    }
    
    return 0;
}