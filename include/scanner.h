//
// Created by Botan on 10/12/19.
//

#ifndef SCRAPPER_SCANNER_H
#define SCRAPPER_SCANNER_H

#include "list.h"
#include <string.h>
#include "stdio.h"

char nextChar(const char *s, int *index);

void searchString(const char * src, long length, char * str, List * content);

int lastIndexOf(const char * src, char c);

int getIndexOf(const char *src, char c, int position);

#endif //SCRAPPER_SCANNER_H
