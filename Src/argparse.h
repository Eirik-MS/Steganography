#pragma once

typedef struct {
    // 1 for distribute, 0 for recover
    int type; 

    char *secret_image;

    int k;
    int n;
    
    char *directory;
} ProgramOptions;

int argparse(int argc, char *argv[], ProgramOptions *options);