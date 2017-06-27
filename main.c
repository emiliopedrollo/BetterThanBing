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

/*#define LAMBDA(c_) ({ c_ _;})*/

void exitWithFailureIfFailed(bool test, char *message);
void readFolder();
void readFiles();

Trie *doNotIndex, *indexedWords;
List *files = NULL;


int main(int argc, char *argv[]){

    struct TrieNode *node;
    bool done = false, firstMatch;
    char words[256] = "dog";
    char *word;
    Connections *connection, *subConnection;

    readFolder();
    readFiles();

    while (!done){
        printf("Type the word to search (or leave empty to exit): ");
        fgets(words,256,stdin);

        if (words[0] == '\n') {
            done = true;
            continue;
        }
    
        word = strtok(words, " \n");
        do {
            if (word == NULL) continue;
            if (searchInTrie(doNotIndex, word) != NULL) {
                printf("Word \"%s\" is on negative list\n",word);
            };
            if ((node = searchInTrie(indexedWords, word)) != NULL){

                printf("%s={",node->word->word);

                connection = node->word->connections;
                firstMatch = true;
                while (connection != NULL){

                    if (!firstMatch) printf(", ");
                    firstMatch = false;

                    printf("{%s, %d",connection->word->word,connection->count);

                    subConnection = connection->word->connections;
                    while (subConnection != NULL){
                        if (subConnection->word != node->word)
                            printf(", %s, %d",subConnection->word->word,subConnection->count);
                        subConnection = subConnection->next;
                    }

                    printf("}");

                    connection = connection->next;
                }

                printf("}\n");
            } else {
                printf("Word \"%s\" was not found on the text files\n",word);
            }


        } while ((word = strtok(NULL, " \n")));

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
    char *word, *last, *tmp;

    FILE * file;

    doNotIndex = newTrieNode();
    indexedWords = newTrieNode();
    struct TrieNode *node, *lastNode;


    if( access( "listanegativa.txt", F_OK ) != -1 && (file = fopen("listanegativa.txt","r"))) {
        while ((word = getNextWord(file)) != NULL){
            if (searchInTrie(doNotIndex, word) == NULL){
                insertToTrie(doNotIndex, word);
            }
        }
        fclose(file);
    }

    fileInList = files;
    while (fileInList != NULL){
        if ((file = fopen((char*)fileInList->info, "r"))){
            while ((last = getNextWord(file)) != NULL && searchInTrie(doNotIndex,last));
            if (last != NULL){

                while ((word = getNextWord(file)) != NULL) {
                    if (searchInTrie(doNotIndex,word)) continue;

                    if ((lastNode = searchInTrie(indexedWords,last)) == NULL) {
                        lastNode = insertToTrie(indexedWords, last);
                    }

                    if ((node = searchInTrie(indexedWords,word)) == NULL) {
                        node = insertToTrie(indexedWords, word);
                    }

                    incrementConnection(node->word,lastNode->word);

                    tmp = last;
                    last = word;
                    free(tmp);
                }
                free(word);
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

            if (strcmp(buffer.gl_pathv[i],"listanegativa.txt") == 0) continue;

            item = addToList(&files,NULL);

            item->info = malloc(strlen(buffer.gl_pathv[i])+1);
            strcpy(item->info,buffer.gl_pathv[i]);

        }
        globfree(&buffer);
    } else
        exitWithFailureIfFailed(true,"Error: glob()");

}