//
// Created by botan on 10/12/19.
//

#ifndef SCRAPPER_SHELL_H
#define SCRAPPER_SHELL_H

#include "stdio.h"

#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"

void println(const char *__restrict __format, ...);

void print(const char *__restrict __format, ...);

void printError(const char *__restrict __format, ...);

void setColor(char *);

void resetColor();


#endif //SCRAPPER_SHELL_H
