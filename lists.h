#ifndef BETTERTHANBING_LIST_H
#define BETTERTHANBING_LIST_H

typedef struct listItem {
    void *info;
    struct listItem *next;
} List;

List *newList();
struct listItem *addToList(List **list, void *info);
void freeList(List **list, void (*func)(void**));
void sortList(List *list, bool (*func)(void*, void*));

#endif /* BETTERTHANBING_LIST_H */
