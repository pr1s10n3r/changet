#pragma once

#include "types.h"

typedef struct
{
    void* value;
    void* next;
} node_t;

typedef struct
{
    node_t* root;
    usize length;
} linked_list_t;

extern node_t* node_create(void* value, void* next);

extern linked_list_t* list_create(node_t* node);
extern void list_add(linked_list_t* list, void* value);
extern node_t* list_get_idx(linked_list_t* list, u64 idx);
extern void list_destroy(linked_list_t* list);
