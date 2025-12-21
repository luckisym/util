Simple util library for common datastructures. Most of these datastructures are made for educational purposes and just for fun. I probably wont be using half of these.

## Linked list
Implemented a doubly linked list, which stores a void pointer to the data, keeps count of # items, adheres to given capacity limits and stores a custom free function which will be used when freeing the linked list.

The following functions are implemented and tested:

Basic init and free functions:
- `l_list_init`
- `l_list_free`
- `ll_item_init`
- `ll_item_free`

Other:
- `l_list_add` - adds given pointer to the linked list.
- `l_list_remove` - removes given pointer from the linked list and frees the data.
- `l_list_contains` - checks if linked list contains given pointer.
- `l_list_size` - counts the number of items in linked list.
- `l_list_is_empty` - checks if linked list is empty
- `l_list_traverse` - traverses the list and executes given function.

Expected arguments and the return value of each function is documented in the code.