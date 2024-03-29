//
// Created by Botan on 10/12/19.
//

#include <shell.h>
#include "string.h"
#include "list.h"

List *createList() {
    List *list = malloc(sizeof(List));

    if (list == NULL) {
        printError("No enough memory !");
        exit(-1);
    }

    list->element = NULL;
    list->length = 0;

    return list;
}

List *createComparableList(comparator c) {
    List *list = createList();
    list->comparator = c;
    return list;
}

void listInsert(List *list, void *value) {
    Element *element = malloc(sizeof(Element));

    if (list && element) {
        element->value = value;
        element->next = list->element;
        list->element = element;
        list->length++;
    }
}

void listFree(List *list) {
    Element *element = list->element;
    while (element != NULL) {
        free(element);
        element = element->next;
    }

    free(list);
}


void foreach(List *list, void (*loop)(void *)) {
    Element *element = list->element;

    while (element) {
        loop(element->value);
        element = element->next;
    }
}

void *listSearch(List *list, void *value) {
    Element *element = list->element;

    while (element) {
        if (list->comparator && list->comparator(value, element->value) == 0)
            return element->value;

        element = element->next;
    }

    return NULL;
}

void listDelete(List *list, void *value) {
    Element *previous = list->element;
    Element *element = list->element;

    while (element) {
        if (list->comparator && list->comparator(value, element->value) == 0) {
            list->length--;

            if (list->element != element)
                previous->next = element->next;
            else
                list->element = element->next;

            free(element);
            break;
        }

        previous = element;
        element = element->next;
    }
}