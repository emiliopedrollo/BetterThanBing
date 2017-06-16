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

LocationInfo *newLocation(void *file)
{
    LocationInfo *location;
    location = malloc(sizeof(LocationInfo));
    location->file = file;
    location->count = 1;
    location->next = NULL;

    return location;
}

/* Returns new trie node (initialized to NULLs) */
Trie *newTrieNode(void)
{
    struct TrieNode *node = NULL;

    node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (node)
    {
        int i;

        node->location = NULL;
        node->isLeaf = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            node->children[i] = NULL;
    }

    return node;
}

/* If not present, inserts key into trie
   If the key is prefix of trie node, just marks leaf node */
void insertToTrie(Trie *root, const char *key, LocationInfo *location)
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
    node->location = location;
    node->isLeaf = true;
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


/*LocationInfo find_in_trie(TRIE *trie, char *word, int layer){
    int i;

    if (trie != NULL){
        for (i=0;i<(*trie).childCount;i++) {
            if (word[layer] == (*trie).childs[i].letter){
                if ((*trie).childs[i].letter == '\0'){
                    return (*trie).childs[i].location[0];
                } else return find_in_trie(&(*trie).childs[i], word, layer + 1);
            }
        }
    }
    return NULL;
}*/