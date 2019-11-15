//
// Created by Botan on 10/12/19.
//
#include <utils.h>
#include "scanner.h"

char nextChar(const char *s, int *index) {
    for (int i = 0; s[i] != 0; i++) {
        if (s[i] != ' ') {
            if (index)
                *index = i;

            return s[i];
        }
    }
    return 0;
}

void searchString(const char *src, long length, char *str, List *content) {
    unsigned long strLength = strlen(str);

    int valid = 0;

    char currentUrl[255];
    int x = 0;

    for (long i = 0; i < length; i++) {
        char c = src[i];

        if (c == str[valid]) {
            valid++;

            if (valid == strLength) {
                i += 3; //jump the =" or ='
                if(src[i - 1] != '\'' && src[i - 1] != '"') {
                    valid = 0;
                    continue;
                }
                while (c != '"' && c != '\'') {
                    c = src[i];
                    currentUrl[x++] = c;
                    i++;
                }
                currentUrl[x - 1] = 0;
                listInsert(content, stringCopy(currentUrl));

                x = 0;
                valid = 0;

                for (int j = 0; j < 255; j++) currentUrl[j] = 0;
            }
        } else {
            valid = 0;
        }
    }
}

int lastIndexOf(const char *src, char c) {
    int lastIndex = 0;
    for (int i = 0; src[i] != 0; i++) {
        if (src[i] == c) {
            lastIndex = i;
        }
    }
    return lastIndex;
}

int getIndexOf(const char *src, char c, int position) {
    int positionCount = 0;
    int lastIndex = 0;
    for (int i = 0; src[i] != 0; i++) {
        if (src[i] == c && positionCount < position) {
            lastIndex = i;
            positionCount++;
        }
    }

    return lastIndex;
}

