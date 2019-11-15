//
// Created by Botan on 10/13/19.
//

#include "utils.h"

char *stringCopy(char *src) {
    char *newStr = malloc(strlen(src) + 1);

    int i = 0;
    for (i = 0; src[i] != 0; i++)
        newStr[i] = src[i];

    newStr[i] = 0;
    return newStr;
}

void trim(char *str) {
    int i;
    int begin = 0;
    int end = strlen(str) - 1;

    while (str[begin] == ' ')
        begin++;

    while ((end >= begin) && str[end] == ' ')
        end--;

    for (i = begin; i <= end; i++)
        str[i - begin] = str[i];

    str[i - begin] = '\0';
}

int getIntegerFromOption(Option *option, int defaultValue) {
    if (option)
        return atoi(option->value);
    return defaultValue;
}

char *getFromOption(Option *option, char *defaultValue) {
    if (option)
        return option->value;
    return defaultValue;
}

char *readFile(FILE *file, long *length) {
    char *buffer = NULL;

    if (file) {
        fseek(file, 0, SEEK_END);
        *length = ftell(file);
        fseek(file, 0, SEEK_SET);

        buffer = malloc(*length);
        if (buffer) {
            fread(buffer, 1, *length, file);
        } else {
            printError("No enough memory !");
            exit(-1);
        }
    }
    return buffer;
}
