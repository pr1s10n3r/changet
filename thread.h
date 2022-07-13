#pragma once

#include "types.h"

typedef struct {
    u64 id;
    char* ext;
    char* filaname;
} post_t;

extern post_t* get_thread_posts(char* board, u64 thread_id);
