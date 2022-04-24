typedef struct HNode {
    char chr;
    int freq;
    struct HNode *left;
    struct HNode *right;
} HNode;


int hnodeCompare(HNode *node1, HNode *node2);

void htreeDestroy(HNode *htree);

HNode *htreeInsert(HNode *htree, int freq, char chr);

