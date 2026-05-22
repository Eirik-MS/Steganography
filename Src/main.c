#include <stdio.h>

#include "argparse.h"

ProgramOptions options = {0};

int main (int argc, char *argv[]) {

    if (argparse(argc, argv, &options) != 0){
        return 1;
    }

    if (options.type){
        printf("Distributing with k=%d and n=%d\n", options.k, options.n);
    } else {
        printf("Recovering with k=%d and n=%d\n", options.k, options.n);
    }
    
    return 0;
}