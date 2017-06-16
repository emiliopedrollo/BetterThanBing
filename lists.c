#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lists.h"

List *newList(){
    return NULL;
}

struct listItem * addToList(List **list, void *info){
    List *new, *list_i;

    new = malloc(sizeof(List));
    new->info = info;
    new->next = NULL;

    if (*list == NULL){
        *list = new;
    } else {
        list_i = *list;
        while (list_i->next != NULL) list_i = list_i->next;
        list_i->next = new;
    }

    return new;
}

void freeList(List **list, void (*func)(void**)){
    List *next;

    if (*list == NULL) return;

    while (*list != NULL) {
        next = (*list)->next;
        func(&((*list)->info));
        free(*list);
        *list = next;
    }
}

void sortList(List *list, bool (*func)(void*, void*)) {

    int i;
    List *iterable = list;
    void *aux;
    int qtd = 0;

    if (list == NULL) return;

    while (iterable != NULL) {
        qtd++;
        iterable = iterable->next;
    }
    for (i = 0; i < qtd; i++) {
        iterable = list;
        while (iterable->next != NULL) {
            if (func(iterable->info, iterable->next->info)) {
                aux = iterable->info;
                iterable->info = iterable->next->info;
                iterable->next->info = aux;
            }
            iterable = iterable->next;
        }
    }

}
