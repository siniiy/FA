#include "functions.h"

status compare_filepaths(char *file_1, char *file_2, int *res) { // Compares two absolute filepaths, uses realpath(), needs <stdlib.h>
    if(!file_1 || !file_2 || !res) return INPUT_ERROR;

    char* temp_1 = realpath(file_1, NULL);
    char* temp_2 = realpath(file_2, NULL);

    if(!temp_1 || !temp_2) {
        free(temp_1);
        free(temp_2);
        return MEMORY_ERROR;
    }

    // printf("%s\n%s\n", temp_1, temp_2);

    *res = strcmp(temp_1, temp_2);
    free(temp_1);
    free(temp_2);
    return OK;
}

status exclude_nums(FILE *in, FILE *out) {
    if (!in || !out) return MEMORY_ERROR;

    int c;
    while ((c = fgetc(in)) != EOF) {
        if (isdigit(c))
            continue;
        fputc(c, out);
    }

    return OK;
}

// сколько раз в строке встречаются символы букв
status count_letters(FILE *in, FILE *out) {
    if (!in || !out) return MEMORY_ERROR;

    int c, count_letters = 0, num_string = 1;

    while ((c = fgetc(in)) != EOF) {
        if(isalpha(c)) count_letters++;
        else if (c == '\n') {
            fprintf(out, "строка №%d, букв латинского алфавита: %d\n", num_string, count_letters);
            count_letters = 0;
            num_string++;
        }
    }

    if (count_letters) fprintf(out, "строка №%d, букв латинского алфавита: %d \n", num_string, count_letters);

    return OK;
}

// сколько раз в строке встречаются символы, отличные от символов букв, цифр, пробел
status count_symbols(FILE *in, FILE *out) {
    if (!in || !out) return MEMORY_ERROR;

    int c, count_letters = 0, num_string = 1;

    while ((c = fgetc(in)) != EOF) {
        if (c == '\n') {
            fprintf(out, "Строка №%d, отличающихся симоволов: %d\n", num_string, count_letters + 1);
            count_letters = 0;
            num_string++;
        }
        else if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ')) count_letters++;
    }

    if (count_letters) fprintf(out, "Строка №%d, отличающихся симоволов: %d\n", num_string, count_letters);

    return OK;
}

//  заменить символы, отличные от символов цифр, ASCII кодом, в 16 СС.
status replace_symbols(FILE *in, FILE *out) {
    if (!in || !out) return MEMORY_ERROR;

    int c, i;
    char num_base16[2];
    while ((c = fgetc(in)) != EOF) {
        if (isdigit(c)) fputc(c, out);
        else {
            i = 0;
            while (c) {
                num_base16[i++] = ((c % 16 > 9) ? (c % 16 - 10 + 'A') : (c % 16 + '0'));
                c /= 16;
            }

            if (i > 0) fputc(num_base16[1], out);
            if (i > 1) fputc(num_base16[0], out);
        }
    }

    return OK;
}