#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "utils.h"


char *build_filepath(const char *dir, const char *filename) {
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

int verify_make_folder(char * filename){
    struct stat st;
    if (mkdir(filename, 0755) == 0) {
        return 1;
    } else if (errno == EEXIST) {
        if (stat("mydir", &st) == 0 && S_ISDIR(st.st_mode)) {
            // It exists and is a directory
            return 1;
        } else {
            return 0;
        }
    } else {
        perror("mkdir");
        return 0;
    }
}


void free_stringlist(StringList_t * list){
    for (int i = 0; i < list->count; ++i) {
        free(list->items[i]);
    }
    free(list->items);
    free(list);
}