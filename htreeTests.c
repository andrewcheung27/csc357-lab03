#include "htree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/* normal tree */
void test1() {
    /* create tree by inserting into NULL */
    HNode *htree = htreeInsert(NULL, 10, 'a');

    htreeInsert(htree, 5, 'c');
    htreeInsert(htree, 5, 'd');  /* freq tie broken by chr */

    htreeInsert(htree, 12, 'd');
    htreeInsert(htree, 11, 'c');
    htreeInsert(htree, 2, 'e');
    htreeInsert(htree, 14, 'a');

    /* root */
    assert(htree->freq == 10);
    assert(htree->chr == 'a');

    /* left */
    assert(htree->left->freq == 5);
    assert(htree->left->chr == 'c');

    /* left left */
    assert(htree->left->left->freq == 2);
    assert(htree->left->left->chr == 'e');
    assert(htree->left->left->left == NULL);
    assert(htree->left->left->right == NULL);

    /* left right */
    assert(htree->left->right->freq == 5);
    assert(htree->left->right->chr == 'd');
    assert(htree->left->right->left == NULL);
    assert(htree->left->right->right == NULL);

    /* right */
    assert(htree->right->freq == 12);
    assert(htree->right->chr == 'd');

    /* right left */
    assert(htree->right->left->freq == 11);
    assert(htree->right->left->chr == 'c');
    assert(htree->right->left->left == NULL);
    assert(htree->right->left->right == NULL);

    /* right right */
    assert(htree->right->right->freq == 14);
    assert(htree->right->right->chr == 'a');
    assert(htree->right->right->left == NULL);
    assert(htree->right->right->right == NULL);

    free(htree);
}


/* everything goes to the right */
void test2() {
    HNode *htree = htreeInsert(NULL, 100, 'f');
    htreeInsert(htree, 101, 'u');
    htreeInsert(htree, 102, 'c');
    htreeInsert(htree, 102, 'k');

    /* root */
    assert(htree->freq == 100);
    assert(htree->chr == 'f');
    assert(htree->left == NULL);

    /* right */
    assert(htree->right->freq == 101);
    assert(htree->right->chr == 'u');
    assert(htree->right->left == NULL);

    /* right right */
    assert(htree->right->right->freq == 102);
    assert(htree->right->right->chr == 'c');
    assert(htree->right->right->left == NULL);

    /* right right right */
    assert(htree->right->right->right->freq == 102);
    assert(htree->right->right->right->chr == 'k');
    assert(htree->right->right->right->left == NULL);

    free(htree);
}


int main (void) {
    test1();
    test2();

    printf("htreeTests: all tests passed\n");
    return 0;
}

