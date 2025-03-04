#include "functions.h"

int main(int argc, char * argv[]){
    if(argc != 3){
        printf("Usage: %s input_file output_file\n", argv[0]);
        return INPUT_ERROR;
    }

    int file_compare_res = 0;

    if((compare_filepaths(argv[1], argv[2], &file_compare_res) != SUCCESS) || !file_compare_res) {
        printf("vsosal\n");
        return INPUT_ERROR;
    }


    FILE * input = fopen(argv[1], "r");
    FILE * output = fopen(argv[2], "w");
    if(!input || !output){
        printf("File openning error\n");
        if(!input) fclose(output);
        if(!output) fclose(input);
        return FILE_OPEN_ERROR;
    }

    int count = 1;
    while (!feof(input)){
        fprintf(output, "tree №%d\n", count);
        print_tree(input, output);
        fprintf(output, "\n");
        count++;
    }

    printf("The trees has been successfully built in %s\n", argv[2]);

    fclose(input);
    fclose(output);
    return 0;
}