#include <stdio.h>

#include "argparse.h"


//TODO: Implement the actual argument parsing logic here. For now, it just prints the arguments.
int argparse(int argc, char *argv[], ProgramOptions *options) {
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
        
    
    }
    return 0;
}