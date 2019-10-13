//
// Created by Botan on 10/13/19.
//

#include "scheduler.h"

List *threads;

void joinThread(pthread_t * threadPtr) {
    pthread_join(*threadPtr, NULL);
}


void startScheduler(Configuration *configuration) {
    threads = createList();
    foreach(configuration->tasks, schedule);
    foreach(threads, joinThread);
}

void schedule(void *taskPtr) {
    Task *task = (Task *) taskPtr;

    if (task) {
        setColor(BLUE);
        pthread_t thread;
        pthread_create(&thread, NULL, startTaskTimer, taskPtr);
        listInsert(threads, &thread);
        println("Task \"%s\": scheduled {%dh %dm %ds} [thread:%lu]", task->name, task->hour, task->minute, task->second, thread);
    }

}

void *startTaskTimer(void *taskPtr) {
    Task *task = (Task *) taskPtr;

    while (1) {
        sleep(task->second + (task->minute * 60) + (task->hour * 3600));
        println("Execute task %s", task->name);
    }

    return 0;
}