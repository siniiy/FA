#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    double eps;

    if (string_to_double(argv[1], &eps) != OK || eps <= 0.0) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    double answers[15];
    char types[5][8] = {"e", "pi", "ln2", "sqrt(2)", "y"};

    if (e_limit(eps, &answers[0]) != OK) return INPUT_ERROR;
    if (pi_limit(eps, &answers[1]) != OK) return INPUT_ERROR;
    if (ln2_limit(eps, &answers[2]) != OK) return INPUT_ERROR;
    if (sqrt_limit(eps, &answers[3]) != OK) return INPUT_ERROR;
    if (y_limit(eps, &answers[4]) != OK) return INPUT_ERROR;

    if (e_row(eps, &answers[5]) != OK) return INPUT_ERROR;
    if (pi_row(eps, &answers[6]) != OK) return INPUT_ERROR;
    if (ln2_row(eps, &answers[7]) != OK) return INPUT_ERROR;
    if (sqrt_row(eps, &answers[8]) != OK) return INPUT_ERROR;
    if (y_row(eps, &answers[9]) != OK) return INPUT_ERROR;

    if (e_equation(eps, &answers[10]) != OK) return INPUT_ERROR;
    if (pi_equation(eps, &answers[11]) != OK) return INPUT_ERROR;
    if (ln2_equation(eps, &answers[12]) != OK) return INPUT_ERROR;
    if (sqrt_equation(eps, &answers[13]) != OK) return INPUT_ERROR;
    if (y_equation(eps, &answers[14]) != OK) return INPUT_ERROR;

    printf("lim:\n");
    for (int i = 0; i < 5; i++) {
        if (answers[i] != INFINITY) {
            printf("%s: %lf\n", types[i], answers[i]);
        }
    }

    printf("\nRow:\n");
    for (int i = 5; i < 10; i++) {
        if (answers[i] != INFINITY) {
            printf("%s: %lf\n", types[i % 5], answers[i]);
        }
    }

    printf("\nEquation:\n");
    for (int i = 10; i < 15; i++) {
        if (answers[i] != INFINITY) {
            printf("%s: %lf\n", types[i % 5], answers[i]);
        }
    }

    return 0;
}