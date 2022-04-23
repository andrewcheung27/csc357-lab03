int main(int argc, char *argv[]) {
    HashTable *ht = htCreate(DEFAULT_HT_SIZE);
    FILE *file;

    long int wordsToCount = DEFAULT_WORDS_TO_COUNT;
    const char *str;
    char *endptr;
    int option;

    /* use getopt to parse args */
    while ((option = getopt(argc, argv, ":n:")) != -1) {
        switch (option) {
            case 'n':
                str = copyString(optarg);
                if (str == NULL) {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }

                wordsToCount = strtol(str, &endptr, 0);
                if (str == endptr) {  /* checks if strtol worked */
                    fprintf(stderr,
                            "Invalid k value (%s).\nusage: fw [-n num] [ file1 [ file 2 ...]\n",
                            optarg);
                    exit(EXIT_FAILURE);
                }
                free((char *) str);
                break;

            case '?':
                fprintf(stderr,
                        "Unknown option.\nusage: fw [-n num] [ file1 [ file 2 ...]\n");
                exit(EXIT_FAILURE);

            case ':':
                fprintf(stderr,
                        "Missing argument.\nusage: fw [-n num] [ file1 [ file 2 ...]\n");
                exit(EXIT_FAILURE);
        }
    }

    /* read from stdin if there are no files provided */
    if (optind == argc) {
        ht = readFile(stdin, ht);
    }

    /* get args that aren't options (should be file names), read files,
     * and put all words in the hash table */
    while (optind < argc) {
        file = fopen(argv[optind], "r");
        if (file == NULL) {
            fprintf(stderr,
                    "%s: No such file or directory\n", argv[optind]);
            optind++;
            continue;
        }
        ht = readFile(file, ht);
        fclose(file);
        optind++;
    }

    /* print the stuff that is to be printed */
    printf("The top %ld words (out of %d) are: \n",
           wordsToCount, ht->numElements);
    printMostCommonWords(ht, wordsToCount);

    /* cleanup */
    htDestroy(ht);
    return 0;
}

