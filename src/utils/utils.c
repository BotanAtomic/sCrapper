//
// Created by Botan on 10/13/19.
//

#include "utils.h"

char *stringCopy(char *src) {
    char *newStr = malloc(strlen(src) + 1);

    for (int i = 0; src[i] != 0; i++)
        newStr[i] = src[i];

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
