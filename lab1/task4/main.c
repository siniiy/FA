#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Input error\n");
        return INPUT_ERROR;
    }
    if (!((argv[1][0] == '-' || argv[1][0] == '/') && (argv[1][2] == '\0' || argv[1][3] == '\0')) || strlen(argv[1]) < 2 || strlen(argv[1]) > 3) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    free(NULL);

    FILE *input = fopen(argv[2], "r");
    if (input == NULL) {
        printf("File open error\n");
        return FILE_OPEN_ERROR;
    }

    FILE *output = NULL;
    char *outfile_path = NULL;
    int len_flag = strlen(argv[1]);

    if (len_flag == 3) {
        if (argc != 4) {
            printf("Input error\n");
            fclose(input);
            return INPUT_ERROR;
        }
        else if (argv[1][1] == 'n') {
            outfile_path = (char *)malloc((strlen(argv[3])) * sizeof(char));
            if (outfile_path == NULL) {
                printf("Memory error\n");
                fclose(input);
                free(outfile_path);
                return MEMORY_ERROR;
            }

            int res = 1;

            if(compare_filepaths(argv[2], argv[3], &res) != OK) {
                fclose(input);
                free(outfile_path);
                printf("Input error\n");
            }

            if(!res) {
                fclose(input);
                free(outfile_path);
                printf("Input error\n");
                return INPUT_ERROR;
            }

            printf("Compare filepaths return: %d\n", res);

            strcpy(outfile_path, argv[3]);
            output = fopen(argv[3], "w");
            if (output == NULL) {
                printf("File open error\n");
                fclose(input);
                return FILE_OPEN_ERROR;
            }
        }
        else {
            printf("Input error\n");
            fclose(input);
            return INPUT_ERROR;
        }
    }
    else {
        if (argc != 3) {
            printf("Input error\n");
            fclose(input);
            return INPUT_ERROR;
        }

        outfile_path = (char *)malloc((strlen(argv[2]) + 6) * sizeof(char));
        if (outfile_path == NULL) {
            printf("Memory error\n");
            fclose(input);
            return MEMORY_ERROR;
        }

        char *end_slesh = strrchr(argv[2], '/');
        if (end_slesh == NULL) {
            strcpy(outfile_path, "out_");
            strcat(outfile_path, argv[2]);
        }
        else {
            int len_end = strlen(end_slesh);
            strncpy(outfile_path, argv[2], strlen(argv[2]) - len_end);
            outfile_path[strlen(argv[2]) - len_end] = '\0';
            strcat(outfile_path, "/out_");
            strcat(outfile_path, end_slesh + 1);
        }

        output = fopen(outfile_path, "w");
        if (output == NULL) {
            printf("File open error\n");
            fclose(input);
            return FILE_OPEN_ERROR;
        }
    }

    switch (argv[1][len_flag - 1]) {
    case 'd':
        if (exclude_nums(input, output) != OK) {
            fclose(input);
            fclose(output);
            free(outfile_path);
            return INPUT_ERROR;
        }

        printf("Арабские цифры удалены,\nИмя файла с результатом: %s\n", outfile_path);
        break;

    case 'i':
        if (count_letters(input, output) != OK) {
            fclose(input);
            fclose(output);
            free(outfile_path);
            return INPUT_ERROR;
        }

        printf("Количество латинских букв в строке подсчитано,\nИмя файла с результатом: %s\n", outfile_path);
        break;
    case 's':
        if (count_symbols(input, output) != OK) {
            fclose(input);
            fclose(output);
            free(outfile_path);
            return INPUT_ERROR;
        }

        printf("Количество символов, отличных от символов букв латинского алфавита, символов арабских цифр и символов пробела подсчитано.\nИмя файла с результатом: %s\n", outfile_path);
        break;
    case 'a':
        if (replace_symbols(input, output) != OK) {
            fclose(input);
            fclose(output);
            free(outfile_path);
            return INPUT_ERROR;
        }

        printf("Символы заменены ASCII кодом в 16СС,\nИмя файла с результатом: %s\n", outfile_path);
        break;
    default:
        printf("Ошибка: флага %s не существует\n", argv[1]);
        fclose(input);
        fclose(output);
        return INPUT_ERROR;
    }

    fclose(input);
    fclose(output);
    free(outfile_path);

    return OK;
}