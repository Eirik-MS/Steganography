#pragma once

typedef struct StringList{
    char **items;
    int count;
    int capacity;
} StringList_t;

void free_stringlist(StringList_t * list);

char *build_filepath(const char *dir, const char *filename);
