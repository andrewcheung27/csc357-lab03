#include "htree.h"

typedef struct ListNode {
    HNode *data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
    int size;
} List;


List *listCreate();

List *listInsert(List *list, HNode *data);

HNode *listRemoveHead(List *list);

