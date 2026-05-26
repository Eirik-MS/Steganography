#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "argparse.h"
#include "utils.h"
#include "env.h"


//TODO: Make more robust int parsing
int argparse(int argc, char *argv[], ProgramOptions *options) {
    #ifdef VERBOSE_DEBUG
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    #endif

    if (argc < 4) {
        fprintf(stderr, "Error: Not enough arguments provided\n");
        return -1;
    }

    //Check first argument for -d or -r
    if (strcmp(argv[1], "-d") == 0) {
        options->distribute = 1;
    } else if (strcmp(argv[1], "-r") == 0) {
        options->distribute = 0;
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
   char *dirptr = NULL;

    for (int i = 2; i < argc; i++) {
        // Process remaining arguments
        if (strcmp(argv[i], "-secret") == 0 && (i + 1 < argc)) {
            options->image_name = argv[++i];
        }
        else if (strcmp(argv[i], "-k") == 0 && (i + 1 < argc)) {
            options->k = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-n") == 0 && (i + 1 < argc)) {
            options->n = atoi(argv[++i]);
            if (!(options->distribute)){
                printf("Warning: '-n' argument is ignored in recovery mode\n");
                options->n = 0;
            }
        }
        else if (strcmp(argv[i], "-dir") == 0 && (i + 1 < argc)) {
            dirptr = argv[++i];
        }
        else {
            fprintf(stderr, "Error: Unknown argument '%s'\n", argv[i]);
            return ARGPARSE_ERROR;
        }
    }

    // In recovery mode, we expect the directory to contain the shares, not a single image file
    if (options->distribute) {
        options->filepath = build_filepath(dirptr, options->image_name);
    } else {
        options->filepath = malloc(strlen(dirptr) + 1);
        memcpy(options->filepath, dirptr, strlen(dirptr) + 1);
        options->filepath[strlen(dirptr)] = '\0';
    }

    if ((options->k < 2 || options->n < options->k) && options->distribute) {
        fprintf(stderr, "Error: requires 2 <= k <= n\n");
        return ARGPARSE_ERROR;
    }else if (options->k >= 10){
        fprintf(stderr, "Error: k value too large, must be less than 10\n");
        return ARGPARSE_ERROR;
    }
    

    return 0;
}

void argparse_free(ProgramOptions *options) {
    if (options == NULL) return;
    free(options->filepath);
    options->filepath = NULL;
}
