//
// Created by botan on 10/12/19.
//

#include "shell.h"

void println(const char *__restrict __format, ...) {
    printf(__format);
    printf("\n");
    resetColor();
    fflush(stdout);
}

void print(const char *__restrict __format, ...) {
    printf(__format);
    resetColor();
    fflush(stdout);
}

void printError(const char *__restrict __format, ...) {
    setColor(RED);
    print(__format);
}

void setColor(char *color) {
    printf("%s", color);
}

void resetColor() {
    printf("\x1B[0m");
}