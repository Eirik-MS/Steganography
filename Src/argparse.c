#include <stdio.h>

#include "argparse.h"

int argparse(int argc, char *argv[], ProgramOptions *options) {
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
        
    
    }
    return 0;
}