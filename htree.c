/* huffman tree */


#include "htree.h"

#include <stdio.h>
#include <stdlib.h>


#define DEFAULT_CODE_LEN 40


int createCodes(HNode *htree, char **codes, char *path, int len) {
    int i;
    char *leftPath;
    char *rightPath;

    if (htree == NULL) {
        return 0;
    }

    /* found a leaf, add code to codes and return 1 */
    if (htree->left == NULL && htree->right == NULL) {
        codes[(unsigned char) htree->chr] = path;
        return 1;
    }

    leftPath = (char *) malloc(sizeof(char) * (len + 1));
    rightPath = (char *) malloc(sizeof(char) * (len + 1));
    if (leftPath == NULL || rightPath == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* leftPath is path + '0', rightPath is path + '1' */
    for (i = 0; i < len; i++) {
        leftPath[i] = path[i];
        rightPath[i] = path[i];
    }
    leftPath[i] = '0';
    rightPath[i] = '1';
    len++;

    /* createCodes left and right. free if it wasn't a leaf */
    if (!createCodes(htree->left, codes, leftPath, len)) {
        free(leftPath);
    }
    if (!createCodes(htree->right, codes, rightPath, len)) {
        free(rightPath);
    }

    /* let previous level of recursion know that this path can be freed */
    return 0;
}


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


void htreeDestroy(HNode *htree) {
    if (htree == NULL) {
        return;
    }

    htreeDestroy(htree->left);
    htreeDestroy(htree->right);
    free(htree);
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
        htree->left = htreeInsert(htree->left, freq, chr);
        return htree;
    }

    /* new node is greater than or equal to current, go right */
    htree->right = htreeInsert(htree->right, freq, chr);
    return htree;
}

