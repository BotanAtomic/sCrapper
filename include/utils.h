//
// Created by Botan on 10/13/19.
//

#ifndef SCRAPPER_UTILS_H
#define SCRAPPER_UTILS_H

#include "string.h"
#include "stdlib.h"
#include "configuration.h"

void trim(char * s);

char * stringCopy(char * src);

int getIntegerFromOption(Option * option, int defaultValue);

char * getFromOption(Option * option, char * defaultValue);

#endif //SCRAPPER_UTILS_H
