//
// Created by botan on 10/12/19.
//

#ifndef SCRAPPER_CONFIGURATION_H
#define SCRAPPER_CONFIGURATION_H

#define ACTION 0
#define OPTION_ACTION 1
#define OPTION_TASK 2
#define TASK 3

#include <stdio.h>
#include "list.h"
#include "string.h"
#include "shell.h"
#include "scanner.h"

struct Task {
    short hour, minute, second;
    char * name;
    List *action;
} typedef Task;

struct Option {
    char *key;
    char *value;
} typedef Option;

struct Action {
    char *name;
    char *url;
    List *options;
} typedef Action;


struct Configuration {
    List *actions;
    List *tasks;
} typedef Configuration;

Task *newTask();

Option *newOption(char *key, char *value);

Action *newAction();

Configuration *newConfiguration();

Configuration *loadConfiguration();

#endif //SCRAPPER_CONFIGURATION_H

