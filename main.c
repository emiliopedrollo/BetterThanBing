#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <stdbool.h>
#include <ctype.h>

void exitWithFailureIfFailed(bool test, char *message);
int readFolder();

char **textFiles = NULL;
int filesCount = 0;

int main(int argc, char *argv[]){

    readFolder();



    exit(EXIT_SUCCESS);

}

void readFiles(){
    char word[256];
    int i,ch;
    int idx=0, sair=0;

    FILE * file;

    for (i=0;i<filesCount;i++){
        file = fopen(textFiles[i],"r");

        do{
            while(!sair) {
                ch = fgetc();
                if(ch == EOF)
                    sair=1;
                else{
                    if (isalnum(ch)) {
                        word[idx++] = (char) tolower(ch);
                    }else{
                        if(idx)
                            sair=1; /* fim da string alfabetica */
                    }
                }
            }
            if(idx){
                word[idx] = '\0';
                printf("%s\n", word);
            }
            sair=idx=0;
        }while(ch!=EOF);

        fclose(file);
    }

}

void exitWithFailureIfFailed(bool test, char *message){

    if (test){
        fprintf(stderr,message);
        exit(EXIT_FAILURE);
    }

}

int readFolder(){
    int i=0;

    int textFilesCap = 2;

    exitWithFailureIfFailed(textFiles != NULL,"Folder already read");

    textFiles = malloc(sizeof(char*)*textFilesCap);

    glob_t buffer;

    if (!glob("*.txt", 0, NULL, &buffer)) {
        for (i=0;  i <buffer.gl_pathc; i++) {

            textFiles[filesCount++] = buffer.gl_pathv[i];

            if (filesCount >= textFilesCap) {
                textFiles = realloc(textFiles, sizeof(char*) * (textFilesCap*=2));
            }

//            printf("%s %d %d\n",buffer.gl_pathv[i],filesCount,textFilesCap);
        }
        globfree(&buffer);
    } else
        exitWithFailureIfFailed(true,"Error: glob()");

}