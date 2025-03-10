#include <stdio.h>
#include <string.h>

void remove_leading_zeros(char *str) {
    // Указатель на первый ненулевой символ
    char *ptr = str;

    // Пропускаем все нули в начале строки
    while (*ptr == '0') {
        ptr++;
    }

    // Если все символы были нулями, оставляем один ноль
    if (*ptr == '\0') {
        str[0] = '0';
        str[1] = '\0'; // Завершаем строку
    } else {
        // Копируем ненулевую часть строки в начало
        strcpy(str, ptr);
    }
}

int ain() {
    char str1[] = "00012345";
    char str2[] = "0000";
    char str3[] = "001234500";

    remove_leading_zeros(str1);
    remove_leading_zeros(str2);
    remove_leading_zeros(str3);

    printf("Result 1: '%s'\n", str1); // Output: '12345'
    printf("Result 2: '%s'\n", str2); // Output: '0'
    printf("Result 3: '%s'\n", str3); // Output: '1234500'

    return 0;
}
