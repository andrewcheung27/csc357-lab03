#include "htree.h"

typedef struct ListNode {
    HNode *data;
    struct ListNode *next;
} ListNode;


typedef struct List {
    ListNode *head;
    int size;
}

