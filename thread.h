#pragma once

#include "types.h"
#include "list.h"
#include <stdbool.h>

typedef struct
{
    const char* ext;
    const char* filename;
} post_t;

typedef struct
{
    post_t* posts;
    usize size;
    bool failed;
} thread_t;

extern linked_list_t* get_thread_posts(char* board, u64 thread_id);

