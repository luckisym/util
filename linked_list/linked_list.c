#include "linked_list.h"

struct l_list *l_list_init(int capacity, void (*free_func) (void *item)) {
    struct l_list *list = malloc(sizeof(struct l_list));
    if (!list) return NULL;

    list->capacity = capacity;
    list->count = 0;
    list->head = NULL;
    list->free_func = free_func;

    return list;
}

struct ll_item *ll_item_init(void *data) {
    struct ll_item *item = malloc(sizeof(struct ll_item));
    if (!item) {
        fprintf(stderr, "Failed to allocate memory\n");
        return NULL;
    }

    item->data = data;
    item->next = NULL;
    item->prev = NULL;
    
    return item;
}

void ll_item_free(struct l_list * list, struct ll_item *item) {
    if(!item || !item->data) return;

    if(list->free_func) list->free_func(item->data);

    item->next = NULL;
    item->prev = NULL;
    item->data = NULL;
}

void l_list_free(struct l_list *list) {
    if (!list) return;

    struct ll_item *curr = list->head;
    while (curr) {
        struct ll_item *next_node = curr->next;

        ll_item_free(list, curr); 
        
        curr = next_node;
    }

    free(list);
}

int l_list_add(struct l_list *list, void *data) {
    if (!list || !data) return 1;

    struct ll_item *new_item = ll_item_init(data);
    if (!new_item) return 1;
    
    if (list->head == NULL) {
        list->head = new_item;
        list->tail = new_item;
    } else {
        new_item->prev = list->tail;
        list->tail->next = new_item;
        list->tail = new_item;
    }

    list->count++;

    return 0;
}

void l_list_remove(struct l_list *list, void *data) {
    if (!list || !data) return;

    struct ll_item *curr = list->head;
    while (curr) {
        if (curr->data == data) {
            if (curr == list->head) {
                list->head = curr->next;
                if (list->head) {
                    list->head->prev = NULL;
                } else {
                    list->tail = NULL;
                }
            } else if (curr == list->tail) {
                list->tail = curr->prev;
                if (list->tail) {
                    list->tail->next = NULL;
                }
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            ll_item_free(list, curr);
            return; 
        } 

        curr = curr->next;
    }
}

int l_list_contains(struct l_list *list, void *data) {
    if (!list || !data) return 0;

    struct ll_item *curr = list->head;
    while (curr) {
        if (curr->data == data) return 1;

        curr = curr->next;
    }

    return 0;
}

int l_list_size(struct l_list *list) {
    if (!list) return -1;

    int count = 0;
    struct ll_item *curr = list->head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    
    return count;
}

int l_list_is_empty(struct l_list *list) {
    if (!list) return -1;

    return list->head ? 0 : 1;
}

int l_list_traverse(struct l_list *list, int (*traverse_func) (void *item), int backwards) {
    if (!list || !traverse_func) return 1;

    struct ll_item *curr = backwards ? list->tail : list->head;
    while (curr) {
        if (!curr->data) return 1;

        if (traverse_func(curr->data)) return 1;

        curr = backwards ? curr->prev : curr->next;
    }

    return 0;
}
