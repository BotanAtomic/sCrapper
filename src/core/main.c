#include <stdio.h>
#include "configuration.h"
#include "shell.h"

int main() {
    if(!loadConfiguration()) {
        printError("Cannot load file configuration");
        return -1;
    }
    return 0;
}