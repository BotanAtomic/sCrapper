//
// Created by botan on 11/14/19.
//

#include "analyser.h"

void extractUrls(FILE *file, char *url, List *urls) {
    long length = 0;
    char * content = readFile(file, &length);

    List * supposedUrls = createList();
    searchString(content, length, "HREF", supposedUrls);

    for (Element *element = supposedUrls->element; element != NULL; element = element->next) {
        char *urlPart = element->value;
        char newUrl[255];

        long l = url[strlen(url) - 1] == '/' ? strlen(url) : lastIndexOf(url, '/') + 1;

        strncpy(newUrl, url, l);
        strcpy(newUrl + l, urlPart);
        newUrl[strlen(urlPart) + l] = 0;
        setColor(CYAN);
        println("\t- Extract URL: %s", newUrl);
        listInsert(urls, stringCopy(newUrl));
    }

    free(content);
}
