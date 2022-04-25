#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define NUM_CHARS 256


void countChars(FILE *file, int *chars) {
    int nextChar;

    while ((nextChar = fgetc(file)) != EOF) {
        chars[nextChar]++;
    }
}


int main(int argc, char *argv[]) {
    int option;
    int i;
    FILE *file;

    int *charHistogram;
    HNode *node1;
    HNode *node2;
    HNode *newNode;
    List *list = listCreate();

    /* use getopt to make sure there are no options */
    while ((option = getopt(argc, argv, ":")) != -1) {
        if (option == '?') {
            fprintf(stderr, 
                    "No options accepted.\nusage: htable filename\n");
            exit(EXIT_FAILURE);
        }
    }

    /* make sure a filename is provided */
    if (optind == argc) {
        fprintf(stderr, "Filename required.\nusage: htable filename\n");
        exit(EXIT_FAILURE);
    }

    /* get filename from args and open file */
    file = fopen(argv[optind++], "r");
    if (file == NULL) {
        fprintf(stderr, 
                "%s: No such file or directory\nusage: htable filename\n", 
                argv[optind]);
        exit(EXIT_FAILURE);
    }

    charHistogram = (int *) malloc(sizeof(int) * NUM_CHARS);
    if (charHistogram == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    /* initialize histogram values to 0 */
    for (i = 0; i < NUM_CHARS; i++) {
        charHistogram[i] = 0;
    }

    /* count characters, insert a huffman tree for each unique character
     * into the sorted list */
    countChars(file, charHistogram);
    fclose(file);
    for (i = 0; i < NUM_CHARS; i++) {
        if (charHistogram[i] > 0) {
            node1 = htreeInsert(NULL, charHistogram[i], i);
            listInsert(list, node1);
        }
    }

    while (list->size > 1) {
        node1 = listRemoveHead(list);
        node2 = listRemoveHead(list);

        /* newNode's freq is the sum of node1 and node2 freq,
         * chr is the smaller of the two chrs for tiebreaking, 
         * left is smaller node and right is larger node */
        newNode = htreeInsert(NULL, node1->freq + node2->freq, 
                node1->chr < node2->chr ? node1->chr : node2->chr);
        if (hnodeCompare(node1, node2) < 0) {
            newNode->left = node1;
            newNode->right = node2;
        }
        else {
            newNode->left = node2;
            newNode->right = node1;
        }
        listInsert(list, newNode);
    }

    /* traverse tree (list->head) to get codes, put codes into table */

    /* cleanup */
    free(charHistogram);
    listDestroy(list);
    return 0;
}

