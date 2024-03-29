//
// Created by Botan on 10/13/19.
//

#ifndef SCRAPPER_PARSER_H
#define SCRAPPER_PARSER_H

#include "configuration.h"
#include "string.h"
#include "utils.h"
#include "comparator.h"

void parseAction(char *line, Action *action, char *error);

void parseActionOption(char *line, Action *action, char *error);

void parseTask(char *line, Task *task, char *error);

void parseTaskOption(char *line, Task *task, Configuration * configuration, char *error);

void parseKeyValue(char *s, char **key, char **value);

void parseListValue(char *s, List *value);

#endif //SCRAPPER_PARSER_H
