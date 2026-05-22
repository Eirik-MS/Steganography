#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "argparse.h"


//TODO: Implement the actual argument parsing logic here. For now, it just prints the arguments.
int argparse(int argc, char *argv[], ProgramOptions *options) {
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    if (argc < 4) {
        fprintf(stderr, "Error: Not enough arguments provided\n");
        return -1;
    }

    //Check first argument for -d or -r
    if (strcmp(argv[1], "-d") == 0) {
        options->type = 1;
    } else if (strcmp(argv[1], "-r") == 0) {
        options->type = 0;
    } else {
        fprintf(stderr, "Error: First argument must be '-d' or '-r'\n");
        return -1;
    }

    /*
    //For robustness can cahnge to 
    //
    //long val = strtol(str, &end, 10);
    //if (errno != 0 || *end != '\0' || end == str) return -1;
    */

    for (int i = 2; i < argc; i++) {
        // Process remaining arguments
        if (strcmp(argv[i], "-secret") == 0 && (i + 1 < argc)) {
            options->secret_image = argv[++i];
        }
        else if (strcmp(argv[i], "-k") == 0 && (i + 1 < argc)) {
            options->k = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-n") == 0 && (i + 1 < argc)) {
            options->n = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-dir") == 0 && (i + 1 < argc)) {
            options->directory = argv[++i];
        }
        else {
            fprintf(stderr, "Error: Unknown argument '%s'\n", argv[i]);
            return -1;
        }
    }

    if (options->k < 2 || options->n < options->k) {
        fprintf(stderr, "Error: requires 2 <= k <= n\n");
        return -1;
    }
    


    return 0;
}