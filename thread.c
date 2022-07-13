#include "thread.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curl/curl.h>

#define MAX_URL_LENGTH 1024

char* build_4chan_url(char* board, u64 thread_id)
{
    char buffer[MAX_URL_LENGTH] = {0};

    int bytes = snprintf(buffer, sizeof(buffer), "https://a.4cdn.org/%s/thread/%lu.json", board, thread_id);
    if (bytes < 0)
        return NULL;

    char* url = (char*)malloc(sizeof(char) * bytes);
    memcpy(url, buffer, bytes);

    return url;
}

post_t* get_thread_posts(char* board, u64 thread_id)
{
    char* url = build_4chan_url(board, thread_id);

    CURL* curl = curl_easy_init();
    if (curl == NULL)
    {
        free(url);

        fprintf(stderr, "ERROR: unable to create curl handle\n");
        return NULL;
    }

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "chatset: utf-8");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl/changet");
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 1);

    CURLcode response = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl = NULL;
    curl_slist_free_all(headers);
    headers = NULL;
    free(url);
    url = NULL;

    if (response != CURLE_OK)
        return NULL;

    int n_posts = 1;
    post_t* posts = malloc(sizeof(post_t) * n_posts);

    return posts;
}
