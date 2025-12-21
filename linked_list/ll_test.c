#include "linked_list.h"
#include <assert.h>
#include <stdint.h>

struct test_obj {
    int value;
};

void test_add() {
    printf("\nTesting add..\n");
    int test_items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    struct l_list *list = l_list_init(10, NULL);
    if (!list) {
        printf("Cant create ll\n");
        return;
    }

    printf("Adding items..\n");
    for (int i = 0; i < 10; i++) {
        l_list_add(list, (void *)(intptr_t)test_items[i]);
    }

    printf("Checking list..\n");
    for (int i = 0; i < 10; i++) {
        assert(l_list_contains(list, (void *)(intptr_t)test_items[i]) == 1);
    }

    printf("Test passed..\n");
    l_list_free(list);
}

void test_remove() {
    printf("\nTesting remove..\n");
    int test_items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    struct l_list *list = l_list_init(10, NULL);
    if (!list) {
        printf("Cant create ll\n");
        return;
    }

    printf("Adding items..\n");
    for (int i = 0; i < 10; i++) {
        l_list_add(list, (void *)test_items[i]);
    }

    printf("Removing items..\n");
    for (int i = 0; i < 10; i++) {
        l_list_remove(list, (void *)test_items[i]);
    }

    printf("Checking list..\n");
    for (int i = 0; i < 10; i++) {
        assert(l_list_contains(list, (void *)test_items[i]) == 0);
    }

    printf("Test passed..\n");
    l_list_free(list);
}

void test_specific_remove() {
    printf("\nTesting specific remove (Head, Tail, Middle)..\n");
    
    struct l_list *list = l_list_init(5, NULL);
    int test_items[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        l_list_add(list, (void *)test_items[i]);
    }

    printf("Removing middle element (30)..\n");
    l_list_remove(list, (void *)30);
    assert(l_list_contains(list, (void *)30) == 0);
    assert(l_list_contains(list, (void *)20) == 1);
    assert(l_list_contains(list, (void *)40) == 1);

    printf("Removing head element (10)..\n");
    l_list_remove(list, (void *)10);
    assert(l_list_contains(list, (void *)10) == 0);
    assert(l_list_contains(list, (void *)20) == 1);

    printf("Removing tail element (50)..\n");
    l_list_remove(list, (void *)50);
    assert(l_list_contains(list, (void *)50) == 0);
    assert(l_list_contains(list, (void *)40) == 1);

    printf("Specific remove tests passed\n");
    l_list_free(list);
}

void test_get_count() {
    printf("\nTesting get_count..\n");
    int test_items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    struct l_list *list = l_list_init(10, NULL);
    if (!list) {
        printf("Cant create ll\n");
        return;
    }

    printf("Adding items..\n");
    for (int i = 0; i < 10; i++) {
        l_list_add(list, (void *)test_items[i]);
    }

    printf("Testing get_count..\n");
    assert(l_list_size(list) == 10);

    l_list_remove(list, (void *)5);

    printf("Testing get_count again, removed 1 item..\n");
    assert(l_list_size(list) == 9);

    printf("Test passed..\n");
    l_list_free(list);
}

void test_is_empty() {
    printf("\nTesting is_empty..\n");
    
    struct l_list *list = l_list_init(5, NULL);
    l_list_add(list, (void *) 50);

    printf("Testing with 1 item in list..\n");
    assert(l_list_is_empty(list) == 0);

    l_list_remove(list, (void *) 50);

    printf("Testing with 0 items in list..\n");
    assert(l_list_is_empty(list) == 1);
    

    printf("Test passed\n");
    l_list_free(list);
}

int custom_traverse(void *data) {
    struct test_obj *obj = (struct test_obj *) data;

    printf("Data: %d\n", obj->value);

    return 0;
}

void custom_free(void *data) {
    free((struct test_obj *) data);
}


void test_traverse() {
    printf("\nTesting traverse..\n");
    struct l_list *list = l_list_init(10, custom_free);
    if (!list) {
        printf("Cant create ll\n");
        return;
    }

    printf("Adding items..\n");
    for (int i = 0; i < 10; i++) {
        struct test_obj *obj = malloc(sizeof(struct test_obj));
        if (!obj) return;

        obj->value = i;
        l_list_add(list, obj);
    }

    printf("Traversing list and printing the items..\n");
    assert(l_list_traverse(list, custom_traverse, 0) == 0);

    printf("Traversing backwards..\n");
    assert(l_list_traverse(list, custom_traverse, 1) == 0);

    printf("Test passed\n");
    l_list_free(list);
}

int main(int argc, char **argv) {

    test_add();
    test_remove();
    test_specific_remove();
    test_get_count();
    test_is_empty();
    test_traverse();

    return 0;
}