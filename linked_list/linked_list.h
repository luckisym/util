#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdlib.h>
#include <stdio.h>

struct l_list {
    int count;
    int capacity;
    struct ll_item *head;
    struct ll_item *tail;
    void (*free_func)(void *item);
};

struct ll_item {
    void *data;
    struct ll_item *next;
    struct ll_item *prev;
};

struct l_list *l_list_init(int capacity, void (*free_func) (void *item));
void l_list_free(struct l_list *list);

struct ll_item *ll_item_init(void *data);
void ll_item_free(struct l_list * list, struct ll_item *item);


int l_list_add(struct l_list *list, void *data);
void l_list_remove(struct l_list *list, void *data);
int l_list_contains(struct l_list *list, void *data);
int l_list_size(struct l_list *list);
int l_list_is_empty(struct l_list *list);
int l_list_traverse(struct l_list *list, int (*traverse_func) (void *item), int backwards);

#endif