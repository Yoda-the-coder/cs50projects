// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Prototypes
bool search(node *head, const char *word);
void free_nodes(node *head);

// Choose number of buckets in hash table
const unsigned int N = 26000;

// Declare global variable to store number of words loaded into dictionary
unsigned int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Initialize variable for hash table bucket
    int bucket = 0;

    // Run word through hash function to return bucket value
    bucket = hash(word);

    // If bucket is null, returns false, else runs word through search function
    if (table[bucket] == NULL)
    {
        return false;
    }
    else
    {
        if (search(table[bucket], word) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Initializes two variables for hash and length of string
    int hash = 0;
    int length = strlen(word);

    // For loop iterates through string, one character at a time (every word is converted to lowercase)
    for (int i = 0; i < length; i++)
    {
        // First hash will total the numerical value of each ascii character
        hash += tolower(word[i]);

        // Iterates between odd & even values of i
        if ((i % 2) == 0)
        {
            hash += (tolower(word[i]) * tolower(word[i]));
        }
        else
        {
            hash *= tolower(word[i]);
        }
        // If not the last character, multiplies current character by the next character
        if (i < (length - 1))
        {
            hash *= tolower(word[i + 1]);
        }
    }
    hash += N;

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    // Initialize memory for word
    char *word = malloc(sizeof(char) * LENGTH + 1);
    if (word == NULL)
    {
        return false;
    }

    // Initialize index for hash table
    int bucket;

    // Load strings, one at a time, into hash table
    while (fscanf(f, "%s", word) != EOF)
    {
        // Initialize new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        // Get bucket from hash function, to insert node into hash table
        bucket = hash(word);

        // Put node into hash table
        n->next = table[bucket];
        table[bucket] = n;

        // Add word to count
        count++;
    }

    free(word);
    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            free_nodes(table[i]);
        }
    }
    return true;
}

bool search(node *head, const char *word)
{
    if (strcasecmp(head->word, word) == 0)
    {
        return true;
    }
    if (head->next == NULL)
    {
        return false;
    }
    else
    {
        return search(head->next, word);
    }
}

void free_nodes(node *head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        free_nodes(head->next);
        free(head);
    }
}