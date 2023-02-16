#include <Clearning/linked_list.h>
#include <stdlib.h>
#include <assert.h>

struct Node *new_node(int data){
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        assert(0 && "Failed to allocate memory for new node");
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

struct Node *find_last_node(struct Node *head){
    struct Node *current_node = head;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    return current_node;
}

struct Node *find_node_at_index(struct Node *head, size_t index){
    if (head == NULL) {
        return NULL;
    }

    struct Node *current_node = head;
    size_t current_index = 0;

    while (current_node-> next != NULL ) {
        current_node = current_node->next;
        current_index++;
        if (current_index == index) {
            break;
        }
    }

    if (current_index != index) {
        return NULL;
    }

    return current_node;
}

LinkedListReturnCode insert_node_at_index(struct Node **pointer_to_head_pointer, struct Node *node, size_t index){
    // Has to pass in a pointer to the head pointer
    // case insert index is 0 (insert at head)
    // HEAD = A -> B -> C, struct Node, 0 -> HEAD = struct Node -> A -> B -> C
    // Modify locally the head pointer is not enough because the caller 
    // This would have problems if there are multiple head pointers to the same linked list
    if (index == 0) {
        node->next = *pointer_to_head_pointer;
        *pointer_to_head_pointer = node;
        return SUCCESS;
    }  

    // case insert index is not 0 (insert at middle or tail)
    // HEAD = A -> B -> C, struct Node, 1 -> HEAD = A -> struct Node -> B -> C
    struct Node *node_before_index = find_node_at_index(*pointer_to_head_pointer, index - 1);
    
    if (node_before_index == NULL) {
        return INDEX_OUT_OF_BOUND;
    }

    node->next = node_before_index->next;
    node_before_index->next = node;

    return SUCCESS;
}

LinkedListReturnCode delete_node_at_index(struct Node **pointer_to_head_pointer, int index)
{
    // case delete index is 0 (delete head)
    // HEAD = A -> B -> C, 0 -> HEAD = B -> C
    if (index == 0) {
        struct Node *node_to_delete = *pointer_to_head_pointer;
        *pointer_to_head_pointer = node_to_delete->next;
        free(node_to_delete);
        return SUCCESS;
    }

    // case delete index is not 0 (delete middle or tail)
    // HEAD = A -> B -> C, 1 -> HEAD = A -> C
    struct Node *node_before_index = find_node_at_index(*pointer_to_head_pointer, index - 1);
    if (node_before_index == NULL) {
        return INDEX_OUT_OF_BOUND;
    }

    struct Node *node_to_delete = node_before_index->next;
    node_before_index->next = node_to_delete->next;
    free(node_to_delete);

    return SUCCESS;
}

struct Node *pop_node_at_index(struct Node **pointer_to_head_pointer, int index){
    // case pop index is 0 (pop head)
    // HEAD = A -> B -> C, 0 -> HEAD = B -> C
    if (index == 0) {
        struct Node *node_to_pop = *pointer_to_head_pointer;
        *pointer_to_head_pointer = node_to_pop->next;
        return node_to_pop;
    }

    // case pop index is not 0 (pop middle or tail)
    // HEAD = A -> B -> C, 1 -> HEAD = A -> C
    struct Node *node_before_index = find_node_at_index(*pointer_to_head_pointer, index - 1);
    if (node_before_index == NULL) {
        // This is an error, but we don't want to assert here
        // the should caller will handle this error
        // NULL means the index is out of bound
        // But there is not a good way to return error code and an object at the same time
        // I wonder if there is a better way to do this
        // like use two separate functions
        // one to get the done 
        // first get the node -> return the node address
        // then remove the node -> return if enum error on failure
        // but is the same problem in the first an address is returned
        // for any function that return a pointer there is not a good way to return an error code
        // I guess this is why the standar is return NULL or assert on fatal error
        // Actually seems that set errno is the way to go
        // It is thread safe 
        //errno = INDEX_OUT_OF_BOUND;
        return NULL;
    }

    struct Node *node_to_pop = node_before_index->next;
    node_before_index->next = node_to_pop->next;
    return node_to_pop;
}

struct Node *search(struct Node *head, int value){
    struct Node *current_node = head;
    while (current_node != NULL) {
        if (current_node->data == value) {
            return current_node;
        }
        current_node = current_node->next;
    }

    return NULL;
}

int length(struct Node *head){
    int length = 0;
    struct Node *current_node = head;
    while (current_node != NULL) {
        length++;
        current_node = current_node->next;
    }

    return length;
}
