#include <stdio.h>

#include "argparse.h"

ProgramOptions options;

int main (int argc, char *argv[]) {


    if (argparse(argc, argv, &options) != 0){
        return 1;
    }

    if (options.distribute){
        printf("Distributing with k=%d and n=%d\n", options.k, options.n);
    } else if (options.recover){
        printf("Recovering with k=%d and n=%d\n", options.k, options.n);
    } else {
        printf("No operation specified.\n");
    }
    
    return 0;
}