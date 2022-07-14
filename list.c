#include "list.h"
#include <stdlib.h>

node_t* node_create(void* value, void* next)
{
    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    node->value = value;
    node->next = next;

    return node;
}

void node_destroy(node_t* node)
{
    if (node == NULL)
        return;

    if (node->value != NULL)
    {
        free(node->value);
        node->value = NULL;
    }

    free(node);
    node = NULL;
}

linked_list_t* list_create(node_t* node)
{
    linked_list_t* new_list = calloc(1, sizeof(linked_list_t));

    if (node != NULL)
        list_add(new_list, node);

    return new_list;
}

void list_add(linked_list_t* list, void* value)
{
    if (list == NULL || value == NULL)
        return;

    if (list->root == NULL)
        list->root = node_create(value, NULL);
    else
    {
        node_t* idx = list->root;
        node_t* prev = NULL;

        while (idx != NULL)
        {
            prev = idx;
            idx = idx->next;
        }

        prev->next = node_create(value, NULL);
    }

    list->length++;
}

node_t* list_get_idx(linked_list_t* list, u64 idx)
{
    if (list == NULL || list->root == NULL)
        return NULL;
    if (idx >= list->length)
        return NULL;

    node_t* node = list->root;
    u64 i = 1;

    while (i <= idx)
    {
        node = node->next;
        i++;
    }

    return node;
}

void list_destroy(linked_list_t* list)
{
    if (list == NULL)
        return;

    node_t* idx = list->root;
    while (idx != NULL)
    {
        node_t* next = idx->next;
        node_destroy(idx);
        idx = next;
    }

    free(list);
    list = NULL;
}

