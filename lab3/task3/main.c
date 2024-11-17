#include "functions.h"

int main(int argc, char **argv) {

    if (inp_validate(argc, argv) == INP_ERROR) {
        printf("Input error gae\n");
        return INP_ERROR;
    }

    Employee *data = NULL;

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("Can't open input file\n");
        return 0;
    }   

    FILE *output = fopen(argv[3], "w+"); // не забыть закрыть
    if(!output) {
        printf("Can't open input file\n");
        return 0;
    }

    int data_size;
    if (read_from_file(input, &data, &data_size) != OK) {
        printf("Error while reading file\n");
        free(data); 
        fclose(input);
        fclose(output);
        return 0;
    }

    switch (argv[2][1]) {
        case 'a':
            //goal;компар А
            qsort(data, data_size, sizeof(Employee), compare_a);
            break;
        case 'd':
            //goal; компар Д
            qsort(data, data_size, sizeof(Employee), compare_d);
            break;
    }
    for(int i = 0; i < data_size; i++) {
        Employee max = data[i];
        // printf("%u\n%s %s\n%f\n", max.id, max.name, max.surname, max.salary);
        fprintf(output, "%u %s %s %f\n", max.id, max.name, max.surname, max.salary);
    }
    
    free(data);
    fclose(input);
    fclose(output);
}

