#include "thread.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <curl/curl.h>
#include <json-c/json.h>

#define MAX_URL_LENGTH 1024

struct response
{
    char* payload;
    size_t size;
};

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

static size_t write_callback(char *body, size_t size, size_t nmemb, void *usrdata)
{
    const size_t rsize = size * nmemb;
    struct response* resp = (struct response*)usrdata;

    char *tmp = realloc(resp->payload, resp->size + rsize + 1);
    if (tmp == NULL)
    {
        fprintf(stderr, "ERROR: unable to reallocate buffer");
        free(resp->payload);
        return 1;
    }

    resp->payload = tmp;
    memcpy(&(resp->payload[resp->size]), body, rsize);

    resp->size += rsize;
    resp->payload[resp->size] = 0x00;

    return rsize;
}

linked_list_t* parse_thread_posts(const char* str)
{
    struct json_object *root = json_tokener_parse(str);
    struct json_object *posts_array = json_object_object_get(root, "posts");

    const usize n_posts = json_object_array_length(posts_array);
    linked_list_t* posts = list_create(NULL);

    for (usize i = 0; i < n_posts; i++)
    {
        struct json_object *post = json_object_array_get_idx(posts_array, i);

        struct json_object *filename = json_object_object_get(post, "filename");
        if (filename == NULL)
            continue;

        struct json_object *ext = json_object_object_get(post, "ext");

        post_t* item = (post_t*)calloc(1, sizeof(post_t));
        item->filename = json_object_get_string(filename),
        item->ext = json_object_get_string(ext),

        list_add(posts, item);
    }

    return posts;
}

linked_list_t* get_thread_posts(char* board, u64 thread_id)
{
    char* url = build_4chan_url(board, thread_id);

    CURL* curl = curl_easy_init();
    if (curl == NULL)
    {
        free(url);
        fprintf(stderr, "ERROR: unable to create curl handle\n");
        return NULL;
    }

    struct response chunk = {.payload = malloc(0), .size = 0};

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "chatset: utf-8");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
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
    {
        free(chunk.payload);
        return NULL;
    }

    linked_list_t* posts = parse_thread_posts(chunk.payload);
    free(chunk.payload);

    return posts;
}

