// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 2500;

// Hash table
int total = 0;
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Check if word match word in dictionary with the same hash code
    int hashed = hash(word);
    
    node *cursor = table[hashed];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Adapted by Neel Mehta based on djb2 of dan bernstein. Code implemented from https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    //Scanf all words from the dictionary
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        //Create a node to store the word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        //Copy the word to the node
        strcpy(n->word, word);
        n->next = NULL;
        
        //Insert the node in a Hash table
        int hashed = hash(word);
        if (table[hashed] == NULL)
        {
            table[hashed] = n;
        }
        else
        {
            n->next = table[hashed];
            table[hashed] = n;
        }
        total++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //Just return total from load
    return total;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //Free all memory
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
