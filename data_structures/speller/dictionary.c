// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 200003 // a prime
unsigned int word_count = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    char lowercase_word[LENGTH + 1];
    for (int i = 0;; i++) {
        lowercase_word[i] = tolower(word[i]);
        if (lowercase_word[i] == '\0') {
            break;
        }
    }
    int hash_value = hash(lowercase_word);
    for (node *ptr = table[hash_value]; ptr != NULL; ptr = ptr->next) {
        if (strcmp(ptr->word, lowercase_word) == 0) {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result *= 114;
        result += *word;
        word++;
    }
    return result % N;
}
// return true if word is successful pushed
bool push(char *word) {
    node *new = malloc(sizeof(node));
    if (new == NULL) {
        return false;
    }
    int hash_value = hash(word);
    strcpy(new->word, word);
    new->next = table[hash_value];
    table[hash_value] = new;
    word_count++;
    return true;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    for (int i = 0; i < N; i++) {
        table[i] = NULL;
    }

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL) {
        return false;
    }

    char word[LENGTH + 1]; // for '\0'
    char buffer;
    int count = 0;
    while (fread(&buffer, sizeof(char), 1, dict) == 1) {
        if (buffer == '\n') {
            word[count] = '\0';
            count = 0;
            bool result = push(word);
            if (result == false) {
                return false;
            }
        } else {
            word[count] = buffer;
            count++;
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) { return word_count; }

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    for (int i = 0; i < N; i++) {
        node *current = table[i];
        while (current != NULL) {
            node *next = current->next;
            free(current);
            current = next;
        }
    }
    return true;
}
