#include "functions.h"

Hash_Table * create_table(int size_hash) {
    Hash_Table * table = (Hash_Table *) malloc(sizeof(Hash_Table));
    if(table == NULL) {
        return NULL;
    }
    table->size = size_hash;

    table->items = (Ht_item**) calloc(size_hash, sizeof(Ht_item*));
    if(table->items == NULL) {
        free(table);
        return NULL;
    }
    return table;
}

int hash_function(char* key) {
    int num = 0;
    int len = strlen(key);

    for (int i = 0; i < len; i++) {
        if (key[i] >= '0' && key[i] <= '9')
            num = num*62 + key[i] - '0';
        else if (key[i] >= 'A' && key[i] <= 'Z')
            num = num*62 + key[i] - 'A' + 10;
        else if (key[i] >= 'a' && key[i] <= 'z') {
            num = num*62 + key[i] - 'a' + 36;
        }        
    }

    if (num < 0) 
        num = -1 * num;
    return num;
}

Ht_item * create_item(char* key, char* value) {
    Ht_item * item = (Ht_item *)malloc(sizeof(Ht_item));
    if(item == NULL) {
        return NULL;
    }

    item->key = (char *) malloc((strlen(key) + 1) * sizeof(char));
    if(item->key == NULL) {
        free(item);
        return NULL;
    }
    strcpy(item->key, key);

    item->value = (char *) malloc((strlen(value) + 1) * sizeof(char));
    if(item->value == NULL) {
        free(item->key);
        free(item);
        return NULL;
    }
    strcpy(item->value, value);

    item->next = NULL;
    item->hash = 0;
    return item;
}

void destroy_item(Ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

Hash_Table * destroy_hashtable(Hash_Table * table) {
    for(int i = 0; i < table->size; ++i) {
        Ht_item* item = table->items[i];
        while(item != NULL) {
            Ht_item* next = item->next;
            destroy_item(item);
            item = next;
        }
    }
    free(table->items);
    free(table);
    return NULL;
}

status insert(Hash_Table* table, char* key, char* value, int hash) {
    int index = hash % table->size;

    Ht_item * item = create_item(key, value);

    item->hash = hash;

    if (table->items[index] == NULL) {
        table->items[index] = item;
    }
    else
    {
        Ht_item* current = table->items[index];
        while (current->next != NULL) {
            if(strcmp(current->key, item->key) == 0)
            {
                return OK;
            }
            current = current->next;
        }
        if(strcmp(current->key, item->key) == 0) {
            return OK;
        }
        current->next = item;
    }
    return OK;
}

void print_hashtable(Hash_Table *table) {
    for (int i = 0; i < table->size; ++i) {
        if(table->items[i]) {
            printf("Bucket %d:\n", i);

            Ht_item *current = table->items[i];
            while (current != NULL)
            {
                printf("  Key: '%s', Value: '%s'\n", current->key, current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

status read_str(FILE * input, char ** buffer, int * capacity, char * c) {
    if(input == NULL || buffer == NULL)
        return NULL_ERROR;

    int idx = 0;
    *c = fgetc(input);
    while(*c != ' ' && *c != '\n' && *c != '\t' && *c != EOF) {
        (*buffer)[idx++] = *c;
        if(*capacity == idx) {
            *capacity *= 2;
            char * for_realloc = (char *) realloc(*buffer, *capacity);
            if(for_realloc == NULL)
            {   
                free(*buffer);
                return INVALID_MEMORY;
            }
            *buffer = for_realloc;
        }
        *c = fgetc(input);
    }
    (*buffer)[idx] = '\0';
    return OK;
}

status read_define(FILE * input, Hash_Table * table, char ** str, char * c, int * capacity_str) {
    if(input == NULL || table == NULL || str == NULL)
        return NULL_ERROR;
    
    int capacity_key = 20, capacity_value = 20;
    char * key = (char *)malloc(capacity_key * sizeof(char));
    if(key == NULL) {
        return INVALID_MEMORY;
    }
    char * value = (char *)malloc(capacity_value * sizeof(char));
    if(value == NULL) {
        free(key);
        return INVALID_MEMORY;
    }

    while(!feof(input)) {
        if(read_str(input, str, capacity_str, c) != OK) {
            free(key);
            free(value);
            return INVALID_MEMORY;
        }
        if(strcmp("#define", *str) == 0) {
            if (read_str(input, &key, &capacity_key, c) != OK)
            {
                free(key);
                free(value);
                return INVALID_MEMORY;
            }
            int idx = 0;
            *c = fgetc(input);
            while(*c != '\n')
            {
                (value)[idx++] = *c;
                if(capacity_value == idx)
                {
                    capacity_value *= 2;
                    char * for_realloc = (char *) realloc(value, capacity_value);
                    if(for_realloc == NULL)
                    {
                        free(key);
                        free(value);
                        return INVALID_MEMORY;
                    }
                    value = for_realloc;
                }
                *c = fgetc(input);
            }
            value[idx] = '\0';
            if (insert(table, key, value, hash_function(key)) != OK) {
                free(key);
                free(value);
                return INVALID_MEMORY;
            }
        }
        else
        {
            break;
        }
    }

    free(key);
    free(value);
    return OK;
}

int check_needs_rebuilding(Hash_Table * table) {
    if(table == NULL)
        return -1;
    int min = INT_MAX;
    int max = 0;
    for (int i = 0; i < table->size; i++) {
        int current_len = 0;
        Ht_item* item = table->items[i];
        if(item == NULL) continue;
        while (item != NULL) {
            current_len++;
            item = item->next;
        }
        if (current_len < min) {
            min = current_len;
        }
        if (current_len > max) {
            max = current_len;
        }
    }
    printf("Min collision: %d\nMax collision: %d\n", min, max);
    double res = (double)max / min;
    if(res >= 2 ) {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is_prime(int num) {
    if(num % 2 == 0) {
        return 0;
    }
    for(int i = 3; i < num / 2; i += 2) {
        if(num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void rebuild_hashtable(Hash_Table * table) {
    int old_size = table->size;
    Ht_item ** old = table->items;
    int new_size = table->size * 2;
    for(; !is_prime(new_size); ++new_size);
    table->size = new_size;

    table->items = (Ht_item **)calloc(new_size, sizeof(Ht_item*));

    for(int i = 0; i < old_size; ++i) {
        Ht_item* item = old[i];
        while (item) {
            insert(table, item->key, item->value, item->hash);
            Ht_item* old_item = item;
            item = item->next;
            destroy_item(old_item);
        }
    }
    free(old);
}

char* ht_search(const Hash_Table* table, char* key) {
    int index = hash_function(key) % table->size;

    Ht_item* item = table->items[index];
    if (item != NULL) {
        if (strcmp(item->key, key) == 0)
            return item->value;
    }

    return NULL;
}

status replace_text(const Hash_Table * table, FILE * input, FILE * output,  char ** str, char * c, int * capacity_str) {
    if(table == NULL || input == NULL || output == NULL)
        return NULL_ERROR;
        
    int flag_stop = 0;

    while(!flag_stop) {
        if (read_str(input, str, capacity_str, c) != OK) 
            return INVALID_MEMORY;

        if (strcmp(*str, "#define") == 0) {
            if (read_str(input, str, capacity_str, c) != OK) 
                return INVALID_MEMORY;

            fprintf(output, "#define %s%c", *str, *c);
        }
        else {
            char * s = ht_search(table, *str);

            if (s) {
                strcpy(*str, s);
            }

            if (*c != EOF) {
                fprintf(output, "%s%c", *str, *c);
            }
            else {
                fprintf(output, "%s", *str);
                flag_stop = 1;
            }
        }
    }
    return OK;
}
    

void replace_file(FILE * input, FILE * output, char * buffer, int size) {
    while (!feof(input)) {
        fgets(buffer, size - 1, input);
        fprintf(output, "%s", buffer);
    }
}