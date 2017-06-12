#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <stdbool.h>
#include <ctype.h>
#include <zconf.h>
#include <string.h>

void exitWithFailureIfFailed(bool test, char *message);
void readFolder();
void readFiles(char **textFiles, int filesCount);

int main(int argc, char *argv[]){

    readFolder();


    exit(EXIT_SUCCESS);

}

char* getNextWord(FILE *file){
    char *word;
    int ch=NULL, cap=4;
    int done=0, idx=0;

    word = malloc(sizeof(char)*4);
    do{
        while(!done) {
            ch = fgetc(file);
            if (ch == EOF) done=1;
            else{
                if (isalnum(ch)) {
                    word[idx++] = (char) tolower(ch);
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

void readFiles(char **textFiles, int filesCount) {
    char *word;
    int i;

    FILE * file;

    if( access( "naoindexar.txt", F_OK ) != -1 && (file = fopen("naoindexar.txt","r"))) {
        while ((word = getNextWord(file)) != NULL){

            printf("%s\n", word);
        }
    }

    for (i=0;i<1;i++){
//        file = fopen(textFiles[i],"r");



//        fclose(file);
    }

}

void exitWithFailureIfFailed(bool test, char *message){

    if (test){
        fprintf(stderr,message);
        exit(EXIT_FAILURE);
    }

}

void readFolder(){

    int i=0;
    char **textFiles = NULL;
    int filesCount = 0;
    int textFilesCap = 2;

    exitWithFailureIfFailed(textFiles != NULL,"Folder already read");

    textFiles = malloc(sizeof(char*)*textFilesCap);

    glob_t buffer;

    if (!glob("*.txt", 0, NULL, &buffer)) {
        for (i=0;  i <buffer.gl_pathc; i++) {

            if (strcmp(buffer.gl_pathv[i],"naoindexar.txt") == 0) continue;

            textFiles[filesCount++] = buffer.gl_pathv[i];

            if (filesCount >= textFilesCap) {
                textFiles = realloc(textFiles, sizeof(char*) * (textFilesCap*=2));
            }

//            printf("%s %d %d\n",textFiles[filesCount-1],filesCount-1,textFilesCap);
        }
        readFiles(textFiles, filesCount);
        globfree(&buffer);
    } else
        exitWithFailureIfFailed(true,"Error: glob()");

}