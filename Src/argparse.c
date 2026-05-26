#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "argparse.h"
#include "env.h"

static char *build_filepath(const char *dir, const char *filename);

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
        }
        else if (strcmp(argv[i], "-dir") == 0 && (i + 1 < argc)) {
            dirptr = argv[++i];
        }
        else {
            fprintf(stderr, "Error: Unknown argument '%s'\n", argv[i]);
            return -1;
        }
    }

    if (dirptr != NULL) {
        options->filepath = build_filepath(dirptr, options->image_name);
    } else {
        options->filepath = build_filepath(dirptr, options->image_name);
    }

    if (options->k < 2 || options->n < options->k) {
        fprintf(stderr, "Error: requires 2 <= k <= n\n");
        return -1;
    }
    


    return 0;
}

void argparse_free(ProgramOptions *options) {
    if (options == NULL) return;
    free(options->filepath);
    options->filepath = NULL;
}

static char *build_filepath(const char *dir, const char *filename) {
    if (filename == NULL || filename[0] == '\0') return NULL;

    if (dir == NULL || dir[0] == '\0') dir = "./";

    size_t dir_len = strlen(dir);
    size_t file_len = strlen(filename);

    // Strip trailing slashes from dir
    if (dir_len > 2 && dir[dir_len - 1] == '/') {
        dir_len--;
    }
    // Strip leading slashes from filename
    if (file_len > 0 && filename[0] == '/') {
        filename++;
        file_len--;
    }
    if (file_len == 0) return NULL;  // filename was just a slash

    // Allocate: dir + '/' + filename + '\0'
    char *result = malloc(dir_len + 1 + file_len + 1);
    if (result == NULL) return NULL;

    memcpy(result, dir, dir_len);
    result[dir_len] = '/';
    memcpy(result + dir_len + 1, filename, file_len);
    result[dir_len + 1 + file_len] = '\0';

    if (access(result, F_OK) != 0) {
        fprintf(stderr, "Error: file '%s' does not exist\n", result);
        free(result);
        return NULL;
    }
    #ifdef VERBOSE_DEBUG
    printf("Constructed filepath: %s\n", result);
    #endif

    return result;
}