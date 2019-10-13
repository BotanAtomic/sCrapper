//
// Created by Botan on 10/13/19.
//

#include "parser.h"

void parseAction(char *line, Action *action, char *error) {
    char *key = NULL;
    char *value = NULL;
    parseKeyValue(line, &key, &value);

    if (!key || !value) {
        *error = 1;
        return;
    }

    if (strcmp(key, "name") == 0) {
        action->name = stringCopy(value);
    } else if (strcmp(key, "url") == 0) {
        action->url = stringCopy(value);
    } else {
        setColor(RED);
        println("Unrecognized key [%s]", key);
        *error = 1;
    }
}

void parseTask(char *line, Task *task, char *error) {
    char *key = NULL;
    char *value = NULL;
    parseKeyValue(line, &key, &value);

    if (!key || !value) {
        *error = 1;
        return;
    }

    char *endPtr = NULL;

    if (strcmp(key, "name") == 0) {
        task->name = stringCopy(value);
    } else if (strcmp(key, "second") == 0) {
        task->second = strtol(value, &endPtr, 10);
    } else if (strcmp(key, "minute") == 0) {
        task->minute = strtol(value, &endPtr, 10);
    } else if (strcmp(key, "hour") == 0) {
        task->hour = strtol(value, &endPtr, 10);
    } else {
        setColor(RED);
        println("Set error for [%s] [%s]", key, value);
        *error = 1;
    }

    if (endPtr != NULL && endPtr == value) {
        setColor(RED);
        println("Invalid value[%s] for key: %s", value, key);
        *error = 1;
    }
}

void parseTaskOption(char *line, Task *task, Configuration *configuration, char *error) {
    char *sCopy = stringCopy(line + 1);
    size_t len = strlen(sCopy);
    if (sCopy[len - 1] == '}')
        sCopy[len - 1] = 0;
    char *token = strtok(sCopy, ",");
    while (token != NULL) {
        trim(token);

        Action *action = listSearch(configuration->actions, token);

        if (!action) {
            *error = 1;
            setColor(RED);
            println("Cannot find action [%s]", token);
            break;
        }

        listInsert(task->action, action);
        token = strtok(NULL, "->");
    }

}

void parseActionOption(char *line, Action *action, char *error) {
    char *key = NULL;
    char *value = NULL;
    parseKeyValue(line, &key, &value);

    if (!key || !value) {
        *error = 1;
        return;
    }

    Option *option = newOption(key, value);
    listInsert(action->options, option);
}

void parseKeyValue(char *s, char **key, char **value) {
    char *sCopy = stringCopy(s + 1);
    size_t len = strlen(sCopy);
    if (sCopy[len - 1] == '}')
        sCopy[len - 1] = 0;
    char *token = strtok(sCopy, "->");
    int i = 0;
    while (token != NULL) {
        if (i > 1) break;
        trim(token);
        *(i % 2 == 0 ? key : value) = token;
        token = strtok(NULL, "->");
        i++;
    }

}
