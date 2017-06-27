#ifndef BETTERTHANBING_TRIE_H
#define BETTERTHANBING_TRIE_H

#include <stdbool.h>


#define ALPHABET_SIZE (37) /* 26 letters + 10 digits + 1 unknown */

typedef struct connections{
    struct word *word;
    struct connections *next;
} Connections;

typedef struct word{
    char *word;
    Connections *connections;
} Word;

typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    Word *word;
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
struct TrieNode * insertToTrie(Trie *root, const char *key);
struct TrieNode *searchInTrie(Trie *root, const char *key);
Word *newWord(char *textWord);
//LocationInfo *newLocation(void *file);

#endif /* BETTERTHANBING_TRIE_H */
