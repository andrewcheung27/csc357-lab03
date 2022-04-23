/* huffman tree */


#include "htree.h"


/* compares nodes based on freq, then chr. returns positive if 
 * node1 > node2, negative if node1 < node2, 0 otherwise */
static int _hnodeCompare(HNode *node1, int node2Freq, char node2Chr) {
    if (node1->freq > node2Freq) {
        return 1;
    }

    if (node1->freq < node2Freq) {
        return -1;
    }

    if (node1->chr > node2Chr) {
        return 1;
    }

    if (node1->chr < node2Chr) {
        return -1;
    }

    return 0;
}


int hnodeCompare(HNode *node1, HNode *node2) {
    return _hnodeCompare(node1, node2->freq, node2->chr);
}


HNode *htreeInsert(HNode *htree, int freq, char chr) {
    if (htree == NULL) {
        HNode *newNode = (HNode *) malloc(sizeof(HNode));

        if (newNode == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        newNode->chr = chr;
        newNode->freq = freq;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    /* new node is less than current, go left */
    if (_hnodeCompare(htree, freq, chr) > 0) {
        htree->left = htreeInsert(htree->left, chr, freq);
        return htree;
    }

    /* new node is greater than or equal to current, go right */
    htree->right = htreeInsert(htree->right, chr, freq);
    return htree;
}

