/* sorted linked list of HNodes */


#include "list.h"


/* inserts huffman node into sorted linked list */
ListNode *listInsert(ListNode *list, HNode *data) {
    ListNode *cur;
    ListNode *prev;

    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;

    if (list == NULL) {
        return node;
    }

    cur = list;
    prev = NULL;
    while (cur != NULL) {
        if (hnodeCompare(cur->data, node->data) < 0) {  /* cur < node */
            prev->next = node;
            node->next = cur;
            return list;
        }
        prev = cur;
        cur = cur->next;
    }

    prev->next = node;
    return list;
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


HNode *listRemoveHead(ListNode *list) {
    HNode *node;

    if (list == NULL) {
        return NULL;
    }

    node = list->next;
    free(list);
    return node;
}

