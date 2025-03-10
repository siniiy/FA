#include "functions.h"

int main() {
    double res[128];

    int len_ans = 0, base = 2;

    double num = 0.1;

    switch (has_a_finite_representation(EPS, base, res, &len_ans, 5, num, .5, 0.25, 0.66, 0.999)) {
    case BASE_ERROR:
        printf("Base error\n");
        return BASE_ERROR;
    case INPUT_ERROR:
        printf("Incorrect numbers\n");
        break;
    case OK:
        if (len_ans) {
            printf("Base: %d, Numbers with finite representation: ", base);
            for (int i = 0; i < len_ans; ++i) {
                printf("%lf ", res[i]);
            }
            putchar('\n');
        }
        else {
            printf("No numbers with finite representation\n");
        }
    }
    return 0;
}