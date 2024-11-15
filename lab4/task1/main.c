#include "functions.h"

int main(int agrc, char * argv[]) {
    if(agrc != 2) {
        printf("Input error\n");
        return 1;
    }

    FILE * filename = fopen(argv[1], "r");
    if(filename == NULL) {
        printf("Fopen 1 error\n");
        return 1;
    }

    FILE * temp = fopen("temp.txt", "w");
    if(temp == NULL) {
        printf("Fopen 2 error\n");
        return 1;
    }

    Hash_Table * table = create_table(HASHSIZE);
    if(table == NULL) {
        fclose(filename);
        return 1;
    }

    int capacity = 20;
    char c;
    char * buffer = (char *)malloc(capacity * sizeof(char));
    if(buffer == NULL) {
        destroy_hashtable(table);
        fclose(filename);
        fclose(temp);
        printf("Malloc error\n");
        return 1;
    }

    if(read_define(filename, table, &buffer, &c, &capacity) != OK) {
        destroy_hashtable(table);
        fclose(filename);
        fclose(temp);
        free(buffer);
        printf("Malloc error\n");
        return 1;
    }
    printf("Hash table has been created\n");
    print_hashtable(table);

    int needs_to_be_rebuilded = check_needs_rebuilding(table);

    if(needs_to_be_rebuilded == -1)
        return 1;

    if(needs_to_be_rebuilded) {
        printf("Hash table after rebuilding\n");
        rebuild_hashtable(table);
        while(check_needs_rebuilding(table))
        {
            rebuild_hashtable(table);
        }
        printf("New size: %d\n", table->size);
        print_hashtable(table);
    }
    else
    {
        printf("Hash table hasn't been rebuilt\n");
    }

    fclose(filename);

    filename = fopen(argv[1], "r");
    if(filename == NULL) {
        printf("Fopen 1 error\n");
        return 1;
    }

    if(replace_text(table, filename, temp, &buffer, &c, &capacity) != OK) {
        free(buffer);
        destroy_hashtable(table);
        fclose(filename);
        fclose(temp);
        printf("Malloc error\n");
        return 1;
    }
    // printf("GOOOOOAL\n");

    fclose(filename);
    fclose(temp);

    filename = fopen(argv[1], "w");
    if(filename == NULL) {
        free(buffer);
        destroy_hashtable(table);
        printf("Fopen 3 error\n");
        return 1;
    }

    temp = fopen("temp.txt", "r");
    if(temp == NULL) {
        free(buffer);
        destroy_hashtable(table);
        fclose(filename);
        printf("Fopen 4 error\n");
        return 1;
    }

    replace_file(temp, filename, buffer, capacity);
    printf("Text replacement is done\n");

    free(buffer);
    destroy_hashtable(table);
    fclose(filename);
    fclose(temp);
    return 0;
}