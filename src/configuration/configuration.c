//
// Created by botan on 10/12/19.
//


#include "configuration.h"
#include "parser.h"
#include "comparator.h"

Task *newTask() {
    Task *task = malloc(sizeof(Task *));
    if (!task) {
        printError("No enough memory !");
        exit(-1);
    }
    task->hour = 0;
    task->minute = 0;
    task->second = 0;
    task->action = createList();
    return task;
}

Option *newOption(char *key, char *value) {
    Option *option = malloc(sizeof(Option *));
    if (!option) {
        printError("No enough memory !");
        exit(-1);
    }
    option->key = stringCopy(key);
    option->value = stringCopy(value);
    return option;
}

Action *newAction() {
    Action *action = malloc(sizeof(Action *));
    if (!action) {
        printError("No enough memory !");
        exit(-1);
    }
    action->options = createComparableList(compareOption);
    return action;
}

Configuration *newConfiguration() {
    Configuration *configuration = malloc(sizeof(Configuration *));
    if (!configuration) {
        printError("No enough memory !");
        exit(-1);
    }
    configuration->actions = createComparableList(compareAction);
    configuration->tasks = createList();
    return configuration;
}

Configuration *loadConfiguration() {
    FILE *configurationFile = fopen("configuration.sconf", "r");

    if (configurationFile == NULL) {
        printError("Configuration file not exists");
        return NULL;
    }

    Configuration *configuration = newConfiguration();

    char *line = NULL;
    size_t length = 0;

    short lineCount = 1;
    char state = -1;

    char error = 0;

    while (getline(&line, &length, configurationFile) != -1) {
        int index = 0;
        char next = nextChar(line, &index);

        size_t lineLength = strlen(line);

        if (next != '#' && next != '\n' && next > 0) { //ignoring comment
            if (next == '=' || next == '+') {
                if (line[lineLength - 1] == '\n')
                    line[lineLength - 1] = 0;

                if (strcmp(line + index, "=") == 0) {
                    state = ACTION;
                    listInsert(configuration->actions, newAction());
                } else if (strcmp(line + index, "==") == 0) {
                    state = TASK;
                    listInsert(configuration->tasks, newTask());
                } else if (strcmp(line + index, "+") == 0 && (state == ACTION || state == TASK)) {
                    state = state == ACTION ? OPTION_ACTION : OPTION_TASK;
                } else {
                    error = 1;
                    break;
                }
            } else if (next == '{' && state != -1) {
                line[strlen(line) - 1] = 0;

                Action *currentAction = NULL;

                if (configuration->actions->element)
                    currentAction = ((Action *) configuration->actions->element->value);

                Task *currentTask = NULL;

                if (configuration->tasks->element)
                    currentTask = ((Task *) configuration->tasks->element->value);


                switch (state) {
                    case ACTION:
                        parseAction(line, currentAction, &error);
                        break;
                    case OPTION_ACTION:
                        parseActionOption(line, currentAction, &error);
                        break;
                    case TASK:
                        parseTask(line, currentTask, &error);
                        break;
                    case OPTION_TASK:
                        parseTaskOption(line, currentTask, configuration, &error);
                        break;
                }

                if (error) break;
            } else {
                error = 1;
                break;
            }
        }

        lineCount++;
    }

    if (error) {
        setColor(RED);
        print("Invalid configuration at line %d : %s", lineCount, line);
        free(configuration);
        configuration = NULL;
    }

    fclose(configurationFile);
    return configuration;
}

