//
// Created by botan on 10/12/19.
//

#include <stdio.h>
#include <scanner.h>
#include "configuration.h"
#include "shell.h"
#include "stdlib.h"

Configuration * newConfiguration() {
    Configuration * configuration = malloc(sizeof(Configuration *));
    if(!configuration) {
        printError("No enough memory !");
        exit(-1);
    }
    configuration->length = 0;
    return configuration;
}

Configuration * loadConfiguration() {
    FILE* configurationFile = fopen("configuration.sconf", "r");

    if(configurationFile == NULL) return NULL;

    Configuration * configuration = newConfiguration();

    char * line = NULL;
    size_t length = 0;

    while(getline(&line, &length, configurationFile) != -1) {
        if(nextChar(line) != '#') { //ignoring comment
            print("%s", line);
        }
    }

    fclose(configurationFile);
    return configuration;
}