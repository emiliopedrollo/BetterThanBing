#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

int charToIndex(int c){
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        if (c >= '0' && c <= '9') { /* numbers */
            c = (int)'z'+1+(c-(int)'0');
        }
        return c - (int)'a';
    } else {
        return ALPHABET_SIZE-1;
    }
}

Word *newWord(char *textWord)
{
    Word *word;
    word = malloc(sizeof(Word));
    word->word = malloc((strlen(textWord)+1)*sizeof(char));
    strcpy(word->word,textWord);
    word->connections = NULL;

    return word;
}

void incrementConnection(Word *word1, Word *word2){
    bool found = false;
    Connections *connections;

    connections = word1->connections;
    while (connections != NULL){
        if (connections->word == word2){
            found = true;
            connections->count++;
            connections = word2->connections;
            while (connections->word != word1) connections = connections->next;
            connections->count++;
            break;
        }
        connections = connections->next;
    }
    if (!found){
        addConnection(word1,word2);
    }
}

void addConnection(Word *word1, Word *word2)
{
    Connections *connections, *connection;
    connections = word1->connections;
    connection = malloc(sizeof(Connections));
    connection->count = 1;
    connection->next = NULL;
    connection->word = word2;
    if (connections == NULL){
        word1->connections = connection;
    } else {
        while (connections->next != NULL) connections = connections->next;
        connections->next = connection;
    }

    connections = word2->connections;
    connection = malloc(sizeof(Connections));
    connection->count = 1;
    connection->next = NULL;
    connection->word = word1;
    if (connections == NULL){
        word2->connections = connection;
    } else {
        while (connections->next != NULL) connections = connections->next;
        connections->next = connection;
    }
}

/* Returns new trie node (initialized to NULLs) */
Trie *newTrieNode(void)
{
    struct TrieNode *node = NULL;

    node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (node)
    {
        int i;

        node->word = NULL;
        node->isLeaf = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            node->children[i] = NULL;
    }

    return node;
}

/* If not present, inserts key into trie
   If the key is prefix of trie node, just marks leaf node */
struct TrieNode *insertToTrie(Trie *root, const char *key)
{
    int level;
    int index;
    size_t length = strlen(key);

    struct TrieNode *node = root;

    for (level = 0; level < length; level++)
    {
        index = charToIndex(tolower(key[level]));
        if (!node->children[index])
            node->children[index] = newTrieNode();

        node = node->children[index];
    }

    /* mark last node as leaf */
    node->word = newWord((char *) key);
    node->isLeaf = true;

    return node;
}

struct TrieNode *searchInTrie(Trie *root, const char *key)
{
    int level;
    int index;
    size_t length = strlen(key);
    struct TrieNode *node = root;

    for (level = 0; level < length; level++)
    {
        index = charToIndex(tolower(key[level]));

        if (!node->children[index])
            return NULL;

        node = node->children[index];
    }

    return (node != NULL && node->isLeaf) ? node : NULL;
}