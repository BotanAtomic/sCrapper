//
// Created by botan on 11/11/19.
//

#include "utils.h"
#include "scrapper.h"
#include <curl/curl.h>
#include <sys/stat.h>

static size_t writeData(void *ptr, size_t size, size_t n, void *stream) {
    size_t written = fwrite(ptr, size, n, (FILE *) stream);
    return written;
}

void createDirectories(char *path) {
    setColor(GREEN);
    println("Create directories if missing at \"%s\"", path);

    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
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

    List *urls = createList();
    listInsert(urls, action->url);

    char path[255];

    if (versioning) {
        sprintf(path, "data/%s/%lu/", action->name, time(NULL));
    } else {
        sprintf(path, "data/%s/", action->name);
    }

    createDirectories(path);

    int i = 0;
    for (Element *element = urls->element; element != NULL && i <= maxDepth; element = element->next) {
        char *url = element->value;
        println("[%s] -> downloading : %s", action->name, url);
        downloadURL(url, path, urls, types);
        i++;
    }
}

void downloadURL(char *url, char *basePath, List *urls, List *types) {
    CURL *curlHandle;
    CURLcode response;
    FILE *file;


    char filePath[255];
    char *fileName = strtok(stringCopy(url), "/");

    char lastUrlChar = url[strlen(url) - 1];

    while (fileName != NULL && lastUrlChar != '/') {
        char *temp = strtok(NULL, "/");
        printf("TEMP = %s\n", temp);

        if (temp && strlen(temp)) {
            fileName = temp;
        } else {
            break;
        }
    }

    if (lastUrlChar == '/') {
        fileName = "index.html";
    }


    curl_global_init(CURL_GLOBAL_ALL);
    curlHandle = curl_easy_init();

    curl_easy_setopt(curlHandle, CURLOPT_URL, url);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 0);

    sprintf(filePath, "%s/%s", basePath, fileName);
    file = fopen(filePath, "wb");

    if (file) {
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, file);
        response = curl_easy_perform(curlHandle);
        fclose(file);

        if (response == CURLE_OK) {
            char *contentType = NULL;
            curl_easy_getinfo(curlHandle, CURLINFO_CONTENT_TYPE, &contentType);

            if (types != NULL && !listSearch(types, contentType)) {
                setColor(RED);
                println("Cannot download url \"%s\" to \"%s\": FORBIDDEN TYPE '%s'", fileName, basePath, contentType);
            } else {
                println("Successfully downloaded \"%s\" at \"%s\" [%s]", fileName, basePath, contentType);
            }
        } else {
            setColor(RED);
            println("Cannot download url \"%s\" to \"%s\"", fileName, basePath);
        }
    } else {
        setColor(RED);
        println("Cannot create file \"%s\" at path \"%s\"", fileName, basePath);
    }

    curl_easy_cleanup(curlHandle);
    curl_global_cleanup();

}
