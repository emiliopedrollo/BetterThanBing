#include <stdio.h>
#include "trie.h"

TRIE *new_trie(){
    return NULL;
}

void add_to_trie(TRIE *trie, char *word){

}

LocationInfo find_in_trie(TRIE *trie, char *word, int layer){
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
}