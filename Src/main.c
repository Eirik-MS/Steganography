#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "argparse.h"
#include "utils.h"
#include "bmp.h"
#include "env.h"

ProgramOptions options = {0};

int main (int argc, char *argv[]) {
    int num_of_img = 0;

    // Parse arguemnts and open the BMP file.
    if (argparse(argc, argv, &options) != 0){
        return ARGPARSE_ERROR;
    }
    


    if (options.distribute){
        //---------------------------------------------------------------------
        //Running the distribution logic
        BMPImage_t Image = {0}; 
        num_of_img = 1;
        printf("Distributing with k=%d and n=%d\n", options.k, options.n);
        if (read_bmp_file(options.filepath, &Image) != 0){
            return BMPFILEHEADER_ERROR;
        }
        //TODO: Implement the distribution logic here. 

 
        free_bmp_img(&Image);
    } else {
        //---------------------------------------------------------------------
        //Finding all the bmp files in the directory
        printf("Recovering with k=%d\n", options.k);
        StringList_t *bmp_files = find_validate_bmp_files(options.filepath);
        num_of_img = bmp_files->count;
        BMPImage_t *ImageList = malloc(sizeof(BMPImage_t)*num_of_img);
        for (int img = 0; img < num_of_img; img++){
            if (read_bmp_file(bmp_files->items[img], &ImageList[img]) != 0){
                free(ImageList);
                return BMPFILEHEADER_ERROR;
            }
        }
        free_stringlist(bmp_files);

        //TODO: Modify images HERE: Using the ImageList and num_of_img variable



        //Free the memmory allocated for the bmp files
        for (int img = 0; img < num_of_img; img++){
            free_bmp_img(&ImageList[img]);
        }
        free(ImageList);
        
            
    }

    //Free the runtime options struct
    argparse_free(&options);
    return 0;
}