#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   DO NOT CHANGE
   1st sample struct containing 2 integers
   When sorting use x first, then y.
**/
typedef struct{
    int x;
    int y;
}istr;

/**
   DO NOT CHANGE
   2nd sample struct containing 3 characters
   When sorting use x first, then y, and finally z.
**/
typedef struct{
    char x;
    char y;
    char z;
}cstr;

typedef struct Node{
    void *data;
    struct Node* next;
}Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    size_t dataSize;
}LinkedList;


/**
   The function takes the pointer to linked list and
   a pointer to data.
   This function adds data at the end of your linked list
   However, the return value is 1 if successfully inserted
   0 otherwise
**/
int add_node(void *ll, void *data){
    LinkedList* list = (LinkedList *) ll;
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = malloc(list->dataSize);
    memcpy(new_node->data, data, list->dataSize);
    if (new_node == NULL) {
        return 0;
    }
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    return 1;
}

/**
   Remove an element at the end of the linked list
   The function takes the pointer to linked list and
   a pointer to return value (removed data)
**/
void remove_node(void *ll, void *ret){
    LinkedList* list = (LinkedList *) ll;
    if (list->head == NULL) {
        return;
    }
    Node *current = list->head;
    Node *prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    if (prev == NULL) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        prev->next = NULL;
        list->tail = prev;
    }
    memcpy(ret, current->data, list->dataSize);
    free(current->data);
    free(current);
}

/**
   This function creates a linked list. This function returns
   the linked list. Returns NULL if creation fails.
   You are required to make your own custom linked list struct
 **/
void *create_ll(size_t size){
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->dataSize = size;
    return list;
}

void merge(Node *left, Node *mid, Node *right, size_t dataSize) {
    LinkedList *tmpList = create_ll(dataSize);
    Node *ptrLeft = left;
    Node *ptrRight = mid->next;

    while (ptrLeft != mid->next && ptrRight != right->next) {
        if (memcmp(ptrLeft->data, ptrRight->data, dataSize) < 0) {
            add_node(tmpList, ptrLeft->data);
            ptrLeft = ptrLeft->next;
        } else {
            add_node(tmpList, ptrRight->data);
            ptrRight = ptrRight->next;
        }
    }
    while (ptrLeft != mid->next) {
        add_node(tmpList, ptrLeft->data);
        ptrLeft = ptrLeft->next;
    }
    while (ptrRight != right->next) {
        add_node(tmpList, ptrRight->data);
        ptrRight = ptrRight->next;
    }
    Node *current = left;
    Node *tmpCurrent = tmpList->head;
    while (current != right->next) {
        memcpy(current->data, tmpCurrent->data, dataSize);
        current = current->next;
        tmpCurrent = tmpCurrent->next;
    }
    while (tmpList->head != NULL) {
        remove_node(tmpList, tmpList->head->data);
    }
    free(tmpList);
}

void merge_sort(Node *left, Node *right, size_t dataSize) {
    if (left == right) {
        return;
    }
    Node *mid = left;
    Node *fast = left;
    while (fast != right && fast->next != right) {
        mid = mid->next;
        fast = fast->next->next;
    }
    merge_sort(left, mid, dataSize);
    merge_sort(mid->next, right, dataSize);
    merge(left, mid, right, dataSize);
}

/**
   This function merge sorts the linked list.
 **/
void sort(void *ll){
    LinkedList *list = (LinkedList *) ll;
    merge_sort(list->head, list->tail, list->dataSize);
}

/**
   Do not modify the function signature of the main function
   including spacing.
 **/
int main(int argc, char** argv){ // Basically do NOT touch this line
    /**
       sample int ll code
       ll* ill = create_ll(sizeof(int));
       int i = 0;
       add(ill, &i);
       i += 1;
       add(ill, &i);
       sort(ill);
       int rv
       remove(ill, $&v);
       printf("%d", rv);
    **/


    return 0;
}

