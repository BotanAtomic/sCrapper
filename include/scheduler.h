//
// Created by Botan on 10/13/19.
//


#ifndef SCRAPPER_SCHEDULER_H
#define SCRAPPER_SCHEDULER_H

#include <pthread.h>
#include <zconf.h>
#include "configuration.h"

void joinThread(pthread_t * thread);

void startScheduler(Configuration *configuration);

void schedule(void * task);

void * startTaskTimer(void *task);

#endif //SCRAPPER_SCHEDULER_H
