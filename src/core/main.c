#include "scheduler.h"
#include "configuration.h"

int main() {
    Configuration *configuration;
    if (!(configuration = loadConfiguration()))
        return -1;

    if(!configuration->tasks->length) {
        printError("Configuration : no task found");
        return -1;
    }

    startScheduler(configuration);

    return 0;
}