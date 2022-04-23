/* sorted linked list of HNodes */


#include "list.h"


List *listCreate() {
    List *list = (List *) malloc(sizeof(List));

    if (list == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    list->head = NULL;
    list->size = 0;

    return list;
}


/* inserts huffman node into sorted linked list */
void listInsert(List *list, HNode *data) {
    ListNode *cur;
    ListNode *prev;
    ListNode *node = listNodeCreate();

    if (list->head == NULL) {
        list->head = node;
        list->head->data = data;
        list->size++;
        return;
    }

    cur = list->head;
    prev = NULL;
    while (cur != NULL) {
        if (hnodeCompare(cur->data, node->data) < 0) {  /* cur < node */
            prev->next = node;
            node->next = cur;
            list->size++;
            return;
        }
        prev = cur;
        cur = cur->next;
    }

    prev->next = node;
    list->size++;
}


static ListNode *listNodeCreate() {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));

    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    node->data = NULL;
    node->next = NULL;

    return node;
}


HNode *listRemoveHead(List *list) {
    HNode *node;
    if (list->head->next != NULL) {

}

