#pragma once

#define ARGPARSE_ERROR -2

typedef struct {
    // 1 for distribute, 0 for recover
    int type; 

    char *image_name;

    int k;
    int n;

    char *filepath;
} ProgramOptions;

int argparse(int argc, char *argv[], ProgramOptions *options);
void argparse_free(ProgramOptions *options);
