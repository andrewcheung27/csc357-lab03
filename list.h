#include "htree.h"

typedef struct ListNode {
    HNode *data;
    struct ListNode *next;
} ListNode;


ListNode *listInsert(ListNode *list, HNode *data);

HNode *listRemoveHead(ListNode *list);

