#include "linked_list.h"
#include <assert.h>
#include <stdint.h> 

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

int main(int argc, char **argv) {

    test_add();
    test_remove();
    test_specific_remove();

    return 0;
}