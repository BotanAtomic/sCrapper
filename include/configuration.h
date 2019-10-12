//
// Created by botan on 10/12/19.
//

#ifndef SCRAPPER_CONFIGURATION_H
#define SCRAPPER_CONFIGURATION_H

#include "list.h"

struct Task {

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

