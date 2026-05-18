#pragma once

typedef struct {
    int distribute;
    int recover;

    char *secret_image;

    int k;
    int n;

    int n_provided;

    char *directory;
} ProgramOptions;

int argparse(int argc, char *argv[], ProgramOptions *options);