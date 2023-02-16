#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

// Linked list node
struct Node{
    int data;
    struct Node *next;
} ;

// Enumeration of possible return codes
typedef enum {
    SUCCESS = 0,
    INDEX_OUT_OF_BOUND = -1,
} LinkedListReturnCode;

// Creates a new node
struct Node *new_node(int data);

// Returns the last node in the linked list
struct Node *find_last_node(struct Node *head);

// Inserts a new node into the linked list at a specific index
LinkedListReturnCode insert_node_at_index(struct Node **pointer_to_head_pointer, struct Node *node, size_t index);

// Deletes a node from the linked list with a given index
LinkedListReturnCode delete_node_at_index(struct Node **pointer_to_head_pointer, int index);

// Pop a node from the linked list at a given index
struct Node *pop_node_at_index(struct Node **pointer_to_head_pointer, int index);

// Searches for a node with a given value in the linked list
struct Node *search(struct Node *head, int value);

// Returns the length of the linked list
int length(struct Node *head);

#endif