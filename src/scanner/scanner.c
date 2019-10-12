//
// Created by Botan on 10/12/19.
//
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

