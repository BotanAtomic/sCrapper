//
// Created by botan on 11/11/19.
//

#include "scrapper.h"
#include <curl/curl.h>
#include <sys/stat.h>

static size_t writeData(void *ptr, size_t size, size_t n, void *stream) {
    size_t written = fwrite(ptr, size, n, (FILE *) stream);
    return written;
}

void createDirectories(char *path) {
    setColor(GREEN);

    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);

    println("Create directories if missing at \"%s\"", tmp);

    len = strlen(tmp);
    if (tmp[len - 1] == '/')
        tmp[len - 1] = 0;
    for (p = tmp + 1; *p; p++)
        if (*p == '/') {
            *p = 0;
            mkdir(tmp, S_IRWXU);
            *p = '/';
        }
    mkdir(tmp, S_IRWXU);
}

void aspire(Action *action) {
    int maxDepth = getIntegerFromOption(listSearch(action->options, "max-depth"), 0);
    char versioning = (char) !strcmp(getFromOption(
            listSearch(action->options, "versioning"), "off"), "on");

    Option *typeOption = listSearch(action->options, "type");

    List *types = typeOption ? typeOption->value : NULL;

    println("Starting task for action \"%s\" [max-depth: %d, versionning: %s]", action->name, maxDepth,
            versioning ? "ON" : "OFF");

    downloadURL(action->url, action, versioning, types, 0, maxDepth);
}

void downloadURL(char *url, Action *action, char versioning, List *types, int count, int max) {
    if (count >= max) {
        return;
    }

    println("[%s] -> downloading : %s", action->name, url);
    CURL *curlHandle;
    CURLcode response;
    FILE *file;

    char filePath[255];
    char *fileName = strtok(stringCopy(url), "/");

    char lastUrlChar = url[strlen(url) - 1];

    while (fileName != NULL && lastUrlChar != '/') {
        char *temp = strtok(NULL, "/");
        if (temp && strlen(temp)) {
            fileName = temp;
        } else {
            break;
        }
    }

    if (lastUrlChar == '/')
        fileName = "index.html";

    char path[255];

    int pathIndex = getIndexOf(url, '/', 3) + 1;
    char *tmpUrl = stringCopy(url);
    tmpUrl[lastIndexOf(tmpUrl, '/')] = 0;
    if (versioning) {
        sprintf(path, "data/%s/%s/%lu/", action->name, tmpUrl + pathIndex, time(NULL));
    } else {
        sprintf(path, "data/%s/%s", action->name, tmpUrl + pathIndex);
    }

    createDirectories(path);

    curl_global_init(CURL_GLOBAL_ALL);
    curlHandle = curl_easy_init();

    curl_easy_setopt(curlHandle, CURLOPT_URL, url);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 0);

    sprintf(filePath, "%s/%s", path, fileName);
    printf("File path: [%s]\n", filePath);
    file = fopen(filePath, "wb+");

    if (file) {
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, file);
        response = curl_easy_perform(curlHandle);

        if (response == CURLE_OK) {
            char *contentType = NULL;
            curl_easy_getinfo(curlHandle, CURLINFO_CONTENT_TYPE, &contentType);

            if (types != NULL && !listSearch(types, contentType)) {
                setColor(RED);
                println("Cannot download url \"%s\" to \"%s\": FORBIDDEN TYPE '%s'", fileName, filePath, contentType);
                remove(filePath);
            } else {
                println("Successfully downloaded \"%s\" at \"%s\" [%s]", fileName, filePath, contentType);

                List *urls = createList();
                extractUrls(file, url, urls);

                Element *element = urls->element;
                while (element) {
                    downloadURL(element->value, action, versioning, types, ++count, max);
                    element = element->next;
                }
            }
        } else {
            setColor(RED);
            println("Cannot download url \"%s\" to \"%s\"", fileName, filePath);
        }
        fclose(file);
    } else {
        setColor(RED);
        println("Cannot create file \"%s\" at path \"%s\"", fileName, filePath);
    }

    curl_easy_cleanup(curlHandle);
    curl_global_cleanup();
}
