#include "functions.h"

status compare_filepaths(char * file_1, char * file_2, int *res) { // Compares two absolute filepaths, uses realpath(), needs <stdlib.h>
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
    return SUCCESS;
}

void print_tree(FILE * input, FILE * output) {
    char c = fgetc(input);
    if(c == '\n' || c == EOF){
        fprintf(output, "->\n");
    }  

    int count = 0;
    while (c != '\n' && c != EOF){
        if(c == '('){
            count++;
        }

        else if(c == ')'){
            count--;
        }

        else if (c == ' ' || c == ','){
            c = fgetc(input);
            continue;
        }

        else{
            for(int i = 0; i < count * 3; ++i){
                fprintf(output, " ");
            }
            fprintf(output, "->%c\n", c);  
        }
        c = fgetc(input);
    }
}