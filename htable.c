#include "htree.h"
#include "list.h"

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
    HNode *hnode;
    ListNode *hlist;

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

    /* charHistogram is used to count how many of each character appear
     * in the file. charHistogram[character] contains its frequency */
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
    for (i = 0; i < NUM_CHARS; i++) {
        if (charHistogram[i] > 0) {
            hnode = htreeInsert(NULL, charHistogram[i], i);
            listInsert(hlist, hnode);
        }
    }

    while (hlist != NULL) {
        /* remove from hlist to get left and right, make new parent of
         * left and right */

    return 0;
}

