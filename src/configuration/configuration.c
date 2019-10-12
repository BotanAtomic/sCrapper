//
// Created by botan on 10/12/19.
//

#include <stdio.h>
#include <scanner.h>
#include "configuration.h"
#include "shell.h"
#include "string.h"

Configuration *newConfiguration() {
    Configuration *configuration = malloc(sizeof(Configuration *));
    if (!configuration) {
        printError("No enough memory !");
        exit(-1);
    }
    configuration->length = 0;
    return configuration;
}

Configuration *loadConfiguration() {
    FILE *configurationFile = fopen("configuration.sconf", "r");

    if (configurationFile == NULL) return NULL;

    Configuration *configuration = newConfiguration();

    char *line = NULL;
    size_t length = 0;

    short lineCount = 0;
    char state = -1;

    while (getline(&line, &length, configurationFile) != -1) {
        int index = 0;
        char next = nextChar(line, &index);
        if (next != '#' && next != '\n' && next > 0) { //ignoring comment
            if(next == '=' || next == '+') {
                if(next == '=')
                    state = line[index + 1] == '=' ? TASK : ACTION;
                else
                    state = OPTION;
            } else {
                line[strlen(line) - 1] = 0;
                println("Line:%d [%s] STATE = %d", lineCount, line, state);
            }


        }

        lineCount++;
    }

    fclose(configurationFile);
    return configuration;
}