#include <stdio.h>

#include "argparse.h"
#include "bmp.h"
#include "env.h"

ProgramOptions options = {0};
BMPImage_t image = {0}; 

int main (int argc, char *argv[]) {

    // Parse arguemnts and open the BMP file.
    if (argparse(argc, argv, &options) != 0){
        return ARGPARSE_ERROR;
    }

    if (options.type){
        printf("Distributing with k=%d and n=%d\n", options.k, options.n);
    } else {
        printf("Recovering with k=%d and n=%d\n", options.k, options.n);
    }

    if (read_bmp_headers(options.filepath, &image) != 0){
        return BMPFILEHEADER_ERROR;
    }

    //TODO: Implement the distribution and recovery logic here.


    bmp_image_free(&image);
    argparse_free(&options);
    return 0;
}