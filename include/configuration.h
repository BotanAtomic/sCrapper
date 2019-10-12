//
// Created by botan on 10/12/19.
//

#ifndef SCRAPPER_CONFIGURATION_H
#define SCRAPPER_CONFIGURATION_H

#define ACTION 0
#define OPTION 1
#define TASK 2

#include "list.h"

struct Task {
    short hour, minute, second;
    char action[255];
} typedef Task;

struct Option {
    char *key;
    char *value;
} typedef Option;

struct Action {
    char name[255];
    char *url;
    List *options;
    char optionLength;
} typedef Action;


struct Configuration {
    short length;
    List *actions;
} typedef Configuration;

Configuration *newConfiguration();

Configuration *loadConfiguration();

#endif //SCRAPPER_CONFIGURATION_H

