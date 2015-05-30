/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality by created hash table.
 *
 * Hana Um
 ***************************************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#define HASHSIZE 1000

typedef struct node 
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

node* hash_table[HASHSIZE];

int hash_function(char* word) {
    int hash = 0;
    int bucket;
    
    for (int i = 0; word[i] != '\0';i++) {
        hash += word[i];
    }
    bucket = hash % HASHSIZE;
    return bucket;
}

// Number of words contained in dictionary.
int num_words = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char new_word[strlen(word) + 1];
    for (int i = 0; i < strlen(word); i++) {
        new_word[i] = tolower(word[i]);
    }
    new_word[strlen(word)] = '\0';
    
    node* cursor = hash_table[hash_function(new_word)];
    while (cursor != NULL) {
        int compare = strcmp(new_word, cursor->word);
        if (compare == 0) 
            return true;
        cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary, "r");
    if (file == NULL) {
        return false;
    }
    
    node* new_node = malloc(sizeof(node));
    //TODO make to lower when loading
    while (fscanf(file, "%s", new_node->word)!= EOF) {
        num_words++;
        int bucket = hash_function(new_node->word);
        if (hash_table[bucket] == NULL) {
            hash_table[bucket] = new_node;
        }    
        else {
            new_node->next = hash_table[bucket];
            hash_table[bucket] = new_node;  
        }
        new_node = malloc(sizeof(node));
    }
    free(new_node);
    
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (num_words > 0)
        return num_words;
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    node* cursor;
    //iterate thrgouh bucket

    for (int i = 0; i < HASHSIZE; i++) {
        cursor = hash_table[i];
        while (cursor != NULL) {
            node* tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            num_words--;
        }
    }

    if (num_words == 0)
        return true;
    else
        return false;
}
