#ifndef BETTERTHANBING_TRIE_H
#define BETTERTHANBING_TRIE_H

#include <stdbool.h>


#define ALPHABET_SIZE (37) /* 26 letters + 10 digits + 1 unknown */

typedef struct li {
    void **file;
    int count;
    struct li *next;
} LocationInfo;


typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    LocationInfo *location;
    bool isLeaf;
} Trie;

/*
typedef struct trie {
    char letter;
    int childCount;
    LocationInfo *location;
    struct trie *childs;
} TRIE;
*/

Trie *newTrieNode(void);
void insertToTrie(Trie *root, const char *key, LocationInfo *location);
struct TrieNode *searchInTrie(Trie *root, const char *key);

LocationInfo *newLocation(void *file);

#endif /* BETTERTHANBING_TRIE_H */
