#ifndef BETTERTHANBING_TRIE_H
#define BETTERTHANBING_TRIE_H

#include <stdbool.h>


#define ALPHABET_SIZE (37) /* 26 letters + 10 digits + 1 unknown */

typedef struct connections{
    struct word *word;
    int count;
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

Trie *newTrieNode(void);
struct TrieNode * insertToTrie(Trie *root, const char *key);
struct TrieNode *searchInTrie(Trie *root, const char *key);
Word *newWord(char *textWord);
void addConnection(Word *word1, Word *word2);
void incrementConnection(Word *word1, Word *word2);

#endif /* BETTERTHANBING_TRIE_H */
