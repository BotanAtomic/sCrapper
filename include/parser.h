//
// Created by Botan on 10/13/19.
//

#ifndef SCRAPPER_PARSER_H
#define SCRAPPER_PARSER_H

#include "configuration.h"
#include "string.h"
#include "utils.h"

void parseAction(char *line, Action *action, char * error);

void parseKeyValue(char *s, char **key, char **value);

#endif //SCRAPPER_PARSER_H
