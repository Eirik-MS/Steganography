#include <stdio.h>

#include "argparse.h"
#include "bmp.h"

//Uncomment for verbose debug output
//#define VERBOSE_DEBUG

ProgramOptions options = {0};

int main (int argc, char *argv[]) {

    if (argparse(argc, argv, &options) != 0){
        return ARGPARSE_ERROR;
    }

    if (options.type){
        printf("Distributing with k=%d and n=%d\n", options.k, options.n);
    } else {
        printf("Recovering with k=%d and n=%d\n", options.k, options.n);
    }

    read_bmp_headers(options.filepath);
    
    argparse_free(&options);
    return 0;
}