#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <stdbool.h>
#include <ctype.h>
#include <zconf.h>
#include <string.h>
#include "trie.h"
#include "utils.h"
#include "lists.h"

#define LAMBDA(c_) ({ c_ _;})

void exitWithFailureIfFailed(bool test, char *message);
void readFolder();
void readFiles();

Trie *doNotIndex, *indexedWords;
List *files = NULL;
List *listOfHits = NULL, *hit;

int main(int argc, char *argv[]){

    struct TrieNode *node;
    LocationInfo *location;
    bool done = false, foundPreviousHit;
    char words[256];
    char *word;

    readFolder();
    readFiles();

    while (!done){
        printf("Type the words to search (or leave empty to exit): ");
        fgets(words,256,stdin);

        if (words[0] == '\n') {
            done = true;
            continue;
        }

        freeList(&listOfHits,  LAMBDA(void _(void **v) { free(*v); }));
        listOfHits = newList();

        word = strtok(words, " \n");
        do {
            if (word == NULL) continue;
            if ((node = searchInTrie(indexedWords, word)) != NULL){
                location = node->location;
                while (location != NULL){

                    foundPreviousHit = false;
                    hit = listOfHits;
                    while (hit != NULL){
                        if (((struct hitsPerFile*)(hit->info))->file == location->file){
                            ((struct hitsPerFile*)(hit->info))->count += location->count;
                            foundPreviousHit = true;
                        }
                        hit = hit->next;
                    }
                    if (!foundPreviousHit){
                        struct hitsPerFile *hits = malloc(sizeof(struct hitsPerFile));
                        hits->file=location->file;
                        hits->count=location->count;
                        addToList(&listOfHits,(void*) hits);
                    }

                    location = location->next;
                }
            }


        } while ((word = strtok(NULL, " \n")));

        sortList(listOfHits,LAMBDA(bool _(void *a, void *b){
            return ((struct hitsPerFile*)a)->count < ((struct hitsPerFile*)b)->count;
        }));

        hit = listOfHits;
        while(hit != NULL){

            printf("The file \"%s\" had %d hit(s) \n",
                   (char*)((struct listItem*)(((struct hitsPerFile*) hit->info)->file))->info,
                   ((struct hitsPerFile*) hit->info)->count);

            hit = hit->next;
        }

    }

    printf("bye bye\n");

    exit(EXIT_SUCCESS);

}

char* getNextWord(FILE *file){
    char *word;
    int ch=EOF, cap=4;
    int done=0, idx=0;
    int a,b,c;

    word = malloc(sizeof(char)*4);
    do{
        while(!done) {
            ch = fgetc(file);
            if (ch == EOF) done=1;
            else{
                if (ch >= 195){
                    a = ch;
                    b = fgetc(file);
                    c = (ch > 200)?fgetc(file):0;
                    ch = getCharFromSet(a,b,c);
                    ch = (ch != 0)?ch:b;
                }
                ch = tolower(ch);
                if (isalnum(ch)) {
                    word[idx++] = (char) ch;
                    if ((idx+1)==cap){
                        word = realloc(word,sizeof(char)*(cap*=2));
                    }
                }else{
                    if(idx) done=1;
                }
            }
        }
        if(idx){
            word[idx] = '\0';
            return word;
        }
        done=idx=0;
    }while(ch!=EOF);
    return NULL;
}

void readFiles() {
    struct listItem *fileInList;
    char *word;
    bool found;

    FILE * file;

    doNotIndex = newTrieNode();
    indexedWords = newTrieNode();
    struct TrieNode *node;
    LocationInfo *location;


    if( access( "naoindexar.txt", F_OK ) != -1 && (file = fopen("naoindexar.txt","r"))) {
        while ((word = getNextWord(file)) != NULL){
            if (searchInTrie(doNotIndex,word) == NULL){
                insertToTrie(doNotIndex,word,NULL);
            }
        }
        fclose(file);
    }

    fileInList = files;
    while (fileInList != NULL){
        if ((file = fopen((char*)fileInList->info, "r"))){
            while ((word = getNextWord(file)) != NULL) {
                if (searchInTrie(doNotIndex,word)) continue;
                if ((node = searchInTrie(indexedWords,word)) == NULL) {
                    insertToTrie(indexedWords, word, newLocation((void*)fileInList));
                } else {
                    location = node->location;
                    found = false;
                    while (location != NULL){
                        if (((struct listItem*)location->file)->info == fileInList->info){
                            location->count++;
                            found = true;
                            break;
                        }
                        location = location->next;
                    }
                    if (!found){
                        location = node->location;
                        while (location->next != NULL) location = location->next;
                        location->next = newLocation((void*)fileInList);
                    }
                }
            }
            fclose(file);
        }
        fileInList = fileInList->next;
    }

}

void exitWithFailureIfFailed(bool test, char *message){

    if (test){
        fprintf(stderr,"%s",message);
        exit(EXIT_FAILURE);
    }

}

void readFolder(){

    int i=0;
    struct listItem *item;

    exitWithFailureIfFailed(files != NULL,"Folder already read");

    files = newList();

    glob_t buffer;

    if (!glob("*.txt", 0, NULL, &buffer)) {
        for (i=0;  i <buffer.gl_pathc; i++) {

            if (strcmp(buffer.gl_pathv[i],"naoindexar.txt") == 0) continue;

            item = addToList(&files,NULL);

            item->info = malloc(strlen(buffer.gl_pathv[i])+1);
            strcpy(item->info,buffer.gl_pathv[i]);

        }
        globfree(&buffer);
    } else
        exitWithFailureIfFailed(true,"Error: glob()");

}