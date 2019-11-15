//
// Created by botan on 11/11/19.
//

#include "configuration.h"
#include "analyser.h"
#include "utils.h"
#include "comparator.h"

#ifndef SCRAPPER_SCRAPPER_H
#define SCRAPPER_SCRAPPER_H

void aspire(Action * action);

void downloadURL(char * url, Action * action, char versioning, List * types, int count, int max);

#endif //SCRAPPER_SCRAPPER_H
