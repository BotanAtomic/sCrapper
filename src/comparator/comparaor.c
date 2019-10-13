//
// Created by Botan on 18/11/18.
//

#include "comparator.h"

char compareAction(void *first, void *second) {
    Action *action = second;
    return (char) strcmp(action->name, (char *) first);
}
