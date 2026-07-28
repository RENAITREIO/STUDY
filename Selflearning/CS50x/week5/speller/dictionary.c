// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // to lower letter
    char lowerword[LENGTH + 1];
    strcpy(lowerword, word);
    for (int i = 0; lowerword[i] != '\0'; i++)
    {
        lowerword[i] = tolower(lowerword[i]);
    }
    // create node for search
    node *search_word = table[hash(word)];
    while (search_word != NULL)
    {
        if (strcmp(lowerword, search_word->word) == 0)
        {
            return true;
        }
        search_word = search_word->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // create FILE *
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }
    // get the word
    char word[LENGTH + 1];
    while (fscanf(source, "%45s", word) != EOF)
    {
        // switch upper word to lower word
        for (int i = 0; word[i] != '\0'; i++)
            word[i] = tolower(word[i]);
        // create node for adding to the tail
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            fclose(source);
            return false;
        }
        strcpy(tmp->word, word);
        unsigned int idx = hash(word);
        tmp->next = table[idx];
        table[idx] = tmp;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        node *count_table = table[i];
        while (count_table != NULL)
        {
            count_table = count_table->next;
            count++;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *count_table = table[i];
        while (count_table != NULL)
        {
            node *tmp = count_table;
            count_table = count_table->next;
            free(tmp);
        }
        free(count_table);
    }
    return true;
}
