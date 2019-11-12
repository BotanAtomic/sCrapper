//
// Created by Botan on 18/11/18.
//

#include "comparator.h"

char compareAction(void *first, void *second) {
    Action *action = second;
    return (char) strcmp(action->name, (char *) first);
}

char compareOption(void *first, void *second) {
    Option *option = second;
    return (char) strcmp(option->key, (char *) first);
}

char compareString(void *first, void *second) {

    printf("Compare %s with %s\n", first, second);

    return (char) strcmp((char *) second, (char *) first);
}

