#include "functions.h"

int main() {
    char *res = NULL;

    puts("\n\ttest 0\n0 + 000000000FFFFFFFFFF; base = 16;\nexpected result: FFFFFFFFFF");
    switch (sum_any_base_all_numbers(&res, 16, 2, "0", "0000000000FFFFFFFFFF")) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case MEMORY_ERROR:
        puts("Memory error\n");
        return MEMORY_ERROR;
        break;
    case OK:
        printf("\t result: %s\n", res);
        free(res);
        break;
    }

    puts("\n\ttest 1\n1 + 000000000FFFFFFFFFF; base = 16;\nexpected result: 10000000000");
    switch (sum_any_base_all_numbers(&res, 16, 2, "1", "000000000FFFFFFFFFF")) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case MEMORY_ERROR:
        puts("Memory error\n");
        return MEMORY_ERROR;
        break;
    case OK:
        printf("\t result: %s\n", res);
        free(res);
        break;
    }

    puts("\n\ttest 2\n123 + 000000000FFFFFFFFFF + ABCFF; base = 16;\nexpected result: 100000ABE21");
    switch (sum_any_base_all_numbers(&res, 16, 3, "123", "0000000000FFFFFFFFFF", "ABCFF")) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case MEMORY_ERROR:
        puts("Memory error\n");
        return MEMORY_ERROR;
        break;
    case OK:
        printf("\t result: %s\n", res);
        free(res);
        break;
    }

    puts("\n\ttest 3\n0 + GOAL; base = 36;\nexpected result: GOAL");
    switch (sum_any_base_all_numbers(&res, 36, 2, "0", "GOAL")) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case MEMORY_ERROR:
        puts("Memory error\n");
        return MEMORY_ERROR;
        break;
    case OK:
        printf("\t result: %s\n", res);
        free(res);
        break;
    }

    puts("\n\ttest 4\n999999998 + 0 + 0 + 2 + 1; base = 10;\nexpected result: 1000000001");
    switch (sum_any_base_all_numbers(&res, 10, 5, "999999998", "0", "0", "2", "1")) {
    case INPUT_ERROR:
        puts("Input error\n");
        return INPUT_ERROR;
        break;
    case MEMORY_ERROR:
        puts("Memory error\n");
        return MEMORY_ERROR;
        break;
    case OK:
        printf("\t result: %s\n", res);
        free(res);
        break;
    }

    puts("\n\ttest 5\n999999998 + 0 + 0 + 2 + 1; base = 10000;\nexpected result: Input error");
    switch (sum_any_base_all_numbers(&res, 10000, 5, "999999998", "0", "0", "2", "1")) {
    case INPUT_ERROR:
        puts("Input error\n");
        // return INPUT_ERROR;
        break;
    case MEMORY_ERROR:
        puts("Memory error\n");
        return MEMORY_ERROR;
        break;
    case OK:
        printf("\t result: %s\n", res);
        free(res);
        break;
    }

    puts("\n\ttest 6\nZ + 1; base = 16;\nexpected result: Input error");
    switch (sum_any_base_all_numbers(&res, 16, 2, "Z", "1")) {
    case INPUT_ERROR:
        puts("Input error\n");
        // return INPUT_ERROR;
        break;
    case MEMORY_ERROR:
        puts("Memory error\n");
        // return MEMORY_ERROR;
        break;
    case OK:
        printf("\t result: %s\n", res);
        free(res);
        break;
    }

    puts("\n\ttest 7\nZVO; base = 36;\nexpected result: Input error");
    switch (sum_any_base_all_numbers(&res, 16, 1, "ZVO")) {
    case INPUT_ERROR:
        puts("Input error\n");
        // return INPUT_ERROR;
        break;
    case MEMORY_ERROR:
        puts("Memory error\n");
        // return MEMORY_ERROR;
        break;
    case OK:
        printf("\t result: %s\n", res);
        free(res);
        break;
    }

    return 0;
}