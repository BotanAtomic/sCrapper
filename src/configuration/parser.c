//
// Created by Botan on 10/13/19.
//

#include "parser.h"

void parseAction(char *line, Action *action, char *error) {
    char *key = NULL;
    char *value = NULL;
    parseKeyValue(line, &key, &value);

    if (strcmp(key, "name") == 0) {
        action->name = stringCopy(value);
    } else if (strcmp(key, "url") == 0) {
        action->url = stringCopy(value);
    } else {
        setColor(RED);
        println("Set error for [%s] [%s]", key, value);
        *error = 1;
    }

}

void parseKeyValue(char *s, char **key, char **value) {
    char *sCopy = stringCopy(s + 1);
    sCopy[strlen(sCopy) - 1] = 0;
    char *token = strtok(sCopy, "->");
    int i = 0;
    while (token != NULL) {
        trim(token);
        *(i % 2 == 0 ? key : value) = token;
        token = strtok(NULL, "->");
        i++;
    }

}
