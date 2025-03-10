#include "functions.h"

// void str_reverse(char *string) {
//     int length = strlen(string) - 1;
//     char *temp = (char*)malloc((length + 1) * sizeof(char));
//     strcpy(temp, string);
//     for(int i = 0; i <= length; i++) {
//         string[i] = temp[length - i];
//     }
//     free(temp);
// }

// status sum_two_numbers_in_any_base(char *first_num, char *second_num, int base, char **result) {
//     if (!first_num || !second_num || !result || base < 2 || base > 36) return INPUT_ERROR;

//     int capacity = strlen(first_num) + 1;
//     char symbols[] = "0123456789ABCDEFGHJKLMNOPQRSTUVWXYZ";

//     *result = (char *)malloc(capacity * sizeof(char));
//     if(!(*result)) return MEMORY_ERROR;
//     strcpy(*result, first_num);

//     char *second = (char*)malloc((strlen(second_num) + 1) * sizeof(char));
//     if(!second) return MEMORY_ERROR;
//     strcpy(second, second_num);

//     str_reverse(*result);
//     str_reverse(second);

//     int number = 0;

//     printf("Result: %s\nSecond: %s\n", *result, second);

//     for(int i = 0; i < strlen(second); i++) { // while(number) + realloc in body of cycle
//         number += (isdigit((*result)[i])) ? ((*result)[i] - '0') : ((*result)[i] - 'A' + 10);
//         number += (isdigit(second[i])) ? (second[i] - '0') : (second[i] - 'A' + 10);

//         (*result)[i] = symbols[number % base];
//         printf("i: %d\nResult: %s\nSecond: %s\nNumber: %d\n", i, *result, second, number);
//         number -= number % base;
//     }

//     if(number) {
//         char* temp = realloc(*result, (strlen(*result) + 2) * sizeof(char));
//         if(!temp) {
//             free(*result);
//             free(second);
//             return MEMORY_ERROR;
//         }
//         *result = temp;
//     }

//     (*result)[strlen(*result) + 1] = '\0';
//     (*result)[strlen(*result)] = symbols[number - 1];

//     str_reverse(*result);

//     free(second);
//     return OK;
// }














status sum_any_base_all_numbers(char **result, int base, int count_numbers, ...) {
    if (base < 2 || base > 36 || !result || count_numbers <= 1) return INPUT_ERROR;

    *result = NULL;
    char *ptr_number, *number;
    int capacity, len_num, len_res;

    va_list args;
    va_start(args, count_numbers);

    ptr_number = va_arg(args, char *);
    len_num = strlen(ptr_number);
    number = (char *)malloc((len_num + 1) * sizeof(char));
    if (!number) {
        va_end(args);
        return MEMORY_ERROR;
    }
    memcpy(number, ptr_number, len_num);
    number[len_num] = '\0';  // Явно устанавливаем нулевой символ
    capacity = len_num * 2 + 1;
    len_res = len_num;
    char *res = (char *)calloc(capacity, sizeof(char));
    if (!res) {
        va_end(args);
        free(number);
        return MEMORY_ERROR;
    }

    if (validate_base(number, base, len_num) != OK) {
        va_end(args);
        free(number);
        free(res);
        return INPUT_ERROR;
    }
    str_reverse(number, len_num);
    memcpy(res, number, len_num);
    res[len_num] = '\0';
    free(number);
    for (int i = 0; i < count_numbers - 1; ++i) {
        ptr_number = va_arg(args, char *);
        len_num = strlen(ptr_number);
        number = (char *)malloc((len_num + 1) * sizeof(char));
        if (!number) {
            va_end(args);
            free(res);
            return MEMORY_ERROR;
        }
        memcpy(number, ptr_number, len_num);
        number[len_num] = '\0';

        if (validate_base(number, base, len_num) != OK) {
            va_end(args);
            free(number);
            free(res);
            return INPUT_ERROR;
        }

        if (len_num + 2 > capacity) {
            char *temp_realloc;
            capacity = len_num * 2 + 1;
            temp_realloc = (char *)realloc(res, capacity * sizeof(char));
            if (!temp_realloc) {
                va_end(args);
                free(number);
                free(res);
                return MEMORY_ERROR;
            }
            res = temp_realloc;
        }

        str_reverse(number, len_num);
        sum_any_base_two_numbers(res, number, base, &len_res, len_num);
        free(number);
    }
    str_reverse(res, len_res);
    *result = res;
    va_end(args);

    int n = 0;
    if ((*result)[0] == '0' && (n = strspn(*result, "0")) != 0 && (*result)[n] != '\0') { 
        int res_length = strlen(*result);
        char *temp = (char*)malloc((res_length - n + 1) * sizeof(char));
        if(!temp) {
            free(res);
            return MEMORY_ERROR;
        }
        memcpy(temp, *result + n, res_length - n);
        temp[res_length - n] = '\0';
        free(*result);
        *result = temp;
    }
    return OK;
}

status validate_base(char *number, int base, int len) {
    if(!number) return INPUT_ERROR;
    if (base < 10) {
        for (int i = 0; i < len; ++i) {
            if (!isdigit(number[i])) return INPUT_ERROR;
        }
    }
    else {
        for (int i = 0; i < len; ++i) {
            number[i] = (char)toupper(number[i]);
            if (!isdigit(number[i]) && (number[i] < 'A' || number[i] > base - 11 + 'A'))
                return INPUT_ERROR;
        }
    }
    return OK;
}

status sum_any_base_two_numbers(char *number1_res, char *number2, int base, int *len_res, int len_number) {
    if(!number1_res || !number2 || !len_res) return INPUT_ERROR;
    int digit_shift = 0, i, digit_1, digit_2, sum;
    for (i = 0; i < *len_res && i < len_number; ++i) {
        digit_1 = isdigit(number1_res[i]) ? number1_res[i] - '0' : number1_res[i] - 'A' + 10;
        digit_2 = isdigit(number2[i]) ? number2[i] - '0' : number2[i] - 'A' + 10;
        sum = digit_1 + digit_2 + digit_shift;
        number1_res[i] = (sum % base) < 10 ? (sum % base) + '0' : (sum % base) + 'A' - 10;
        digit_shift = sum / base;
    }

    if (len_number > *len_res) {
        for (; i < len_number; ++i) {
            digit_2 = isdigit(number2[i]) ? number2[i] - '0' : number2[i] - 'A' + 10;
            sum = digit_2 + digit_shift;
            number1_res[i] = (sum % base) < 10 ? (sum % base) + '0' : (sum % base) + 'A' - 10;
            digit_shift = sum / base;
        }
    }
    else {
        for (; i < *len_res; ++i) {
            digit_1 = isdigit(number1_res[i]) ? number1_res[i] - '0' : number1_res[i] - 'A' + 10;
            sum = digit_1 + digit_shift;
            number1_res[i] = (sum % base) < 10 ? (sum % base) + '0' : (sum % base) + 'A' - 10;
            digit_shift = sum / base;
        }
    }
    *len_res = (len_number > *len_res) ? len_number : *len_res;
    number1_res[*len_res] = '\0';
    if (digit_shift) {
        number1_res[i++] = digit_shift < 10 ? digit_shift + '0' : digit_shift + 'A' - 10;
        number1_res[i] = '\0';
        *len_res = i;
    }
    return OK;
}

status str_reverse(char *str, int len) {
    if(!str) return INPUT_ERROR;
    char temp;
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return OK;
}