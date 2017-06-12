#ifndef BETTERTHANBING_TRIE_H
#define BETTERTHANBING_TRIE_H

#include <stdbool.h>

typedef struct li {
    int fileIndex;
    int count;
    struct li *next;
} LocationInfo;

typedef struct trie {
    char letter;
    int childCount;
    LocationInfo *location;
    struct trie *childs;
} TRIE;

#endif //BETTERTHANBING_TRIE_H
