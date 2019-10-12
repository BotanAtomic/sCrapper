//
// Created by Botan on 10/12/19.
//

#ifndef SCRAPPER_LIST_H
#define SCRAPPER_LIST_H


#include <stdlib.h>
typedef char (*comparator)(void *, void *);

typedef struct Element {
    void *value;
    struct Element *next;
} Element;

typedef struct List {
    Element *element;
    short length;
    comparator comparator;
} List;

List *createList();

List *createComparableList(comparator c);

void listInsert(List *, void *);

void listFree(List *);

void foreach(List *, void (*)(void *));

void *listSearch(List *, void *);

void listDelete(List *, void *);

#endif //SCRAPPER_LIST_H
