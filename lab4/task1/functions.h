#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define HASHSIZE 128
#define EPSILON 1e-6

typedef enum status
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    ERROR_OPEN_FILE,
    NULL_ERROR
}status;

typedef struct Ht_item
{
    int hash;
    char * key;
    char * value;
    struct Ht_item * next;
} Ht_item;

typedef struct Hash_Table
{
    Ht_item ** items;
    int size;
} Hash_Table;

Hash_Table * create_table(int size_hash);
int hash_function(char* key);
Ht_item * create_item(char* key, char* value);
void destroy_item(Ht_item* item);
Hash_Table * destroy_hashtable(Hash_Table * table);
status insert(Hash_Table* table, char* key, char* value, int hash);
void print_hashtable(Hash_Table *table);
status read_str(FILE * input, char ** buffer, int * capacity, char * c);
status read_define(FILE * input, Hash_Table * table, char ** str, char * c, int * capacity_str);
int check_needs_rebuilding(Hash_Table * table);
int is_prime(int num);
void rebuild_hashtable(Hash_Table * table);
char* ht_search(const Hash_Table* table, char* key);
status replace_text(const Hash_Table * table, FILE * input, FILE * output,  char ** str, char * c, int * capacity_str);
void replace_file(FILE * input, FILE * output, char * buffer, int size);

#endif