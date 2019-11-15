//
// Created by botan on 11/14/19.
//

#ifndef SCRAPPER_ANALYSER_H
#define SCRAPPER_ANALYSER_H

#include "list.h"
#include <stdio.h>
#include "utils.h"

void extractUrls(FILE * file, char * url, List * urls);

#endif //SCRAPPER_ANALYSER_H
