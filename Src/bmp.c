#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "utils.h"
#include "env.h"
#include "bmp.h"

static int has_bmp_extension(const char *filename);

int read_bmp_file(char * filepath, BMPImage_t *image){
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filepath);
        return BMPFILEHEADER_ERROR;
    }
    
    
    fread(&image->fileHeader, sizeof(BMPFileHeader_t), 1, file);

    if (image->fileHeader.bfType[0] != 'B' || image->fileHeader.bfType[1] != 'M') {
        #ifdef VERBOSE_DEBUG
        fprintf(stderr, "Error: Not a valid BMP file\n (Invalid signature: %c%c)\n", image->fileHeader.bfType[0], image->fileHeader.bfType[1]);
        #endif
        fclose(file);
        return BMPFILEHEADER_ERROR;
    }

    fread(&image->infoHeaderSize, sizeof(uint32_t), 1, file);

    if (image->infoHeaderSize != 40) {
        #ifdef VERBOSE_DEBUG
        fprintf(stderr, "Error: Unsupported BMP header size: %d\n", image->infoHeaderSize);
        #endif
        fclose(file);
        return BMPFILEHEADER_ERROR;
    }


    fread(&image->infoHeader, sizeof(BMPImageHeader_t), 1, file);
    image->width = image->infoHeader.biWidth;
    image->height = image->infoHeader.biHeight;

    fseek(file, image->fileHeader.pxOffsetBits, SEEK_SET);
    image->pixel = malloc(image->infoHeader.biSizeImage);
    if (image->pixel == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for pixel data\n");
        fclose(file);
        return ENOMEM;
    }
    fread(image->pixel, 1, image->infoHeader.biSizeImage, file);
    
    #ifdef VERBOSE_DEBUG
    printFileHeader(image->fileHeader);
    printImageHeader(image->infoHeader);
    #endif
    
    fclose(file);
    return 0;
}

StringList_t *find_validate_bmp_files(char * filepath){
    // Arbitrary initial size, will be resized if needed.
    StringList_t *list = malloc(sizeof(StringList_t));
    list->items = malloc(sizeof(char*) * 10);
    list->count = 0;
    list->capacity = 10;
    struct dirent *entry;

    DIR *dir = opendir(filepath);

    if (dir == NULL) {
        fprintf(stderr, "Could not open directory %s\n", filepath);
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (has_bmp_extension(entry->d_name)) {
            char* combined_path = build_filepath(filepath, entry->d_name);
            if (combined_path == NULL) {
                fprintf(stderr, "Could not build path to file %s\n", entry->d_name);
                continue;
            }
            FILE *file = fopen(combined_path, "rb");
            BMPFileHeader_t fileHeader;
            if (file == NULL) {
                fprintf(stderr, "Could not open file %s\n", entry->d_name);
                continue;
            }
            fread(&fileHeader, sizeof(BMPFileHeader_t), 1, file);
            if (fileHeader.bfType[0] != 'B' || fileHeader.bfType[1] != 'M') {
                fprintf(stderr, "Error: Not a valid BMP file: %s\n", entry->d_name);
                fclose(file);
                continue;
            }
            list->items[list->count++] = combined_path;
            fclose(file);            
            
        }

        //Incrementally resize the list if we exceed capacity
        if (list->count >= list->capacity) {
            list->capacity *= 2;
            char **new_list = realloc(list->items, sizeof(char*) * list->capacity);
            if (new_list == NULL) {
                fprintf(stderr, "Error: Could not reallocate memory for file list\n");
                free(list);
                closedir(dir);
                return NULL;
            }
            list->items = new_list;
        }
    }    

    closedir(dir);
    return list;
}



void free_bmp_img(BMPImage_t *image) {
    if (image->pixel) {
        free(image->pixel);
        image->pixel = NULL;
    }
    if (image->colorTab) {
        free(image->colorTab);
        image->colorTab = NULL;
    }
}


static int has_bmp_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return 0;
    return strcmp(dot, ".bmp") == 0;
}

void printFileHeader(BMPFileHeader_t fileHeader) {
   printf("\nType: %c%c.\n", fileHeader.bfType[0],fileHeader.bfType[1]);
   printf("Size: %d.\n", fileHeader.bfSize);
   printf("Verify (Must be 0 0): %d %d.\n" ,fileHeader.__bfReserved1, fileHeader.__bfReserved2);
   printf("Offset : %d.\n", fileHeader.pxOffsetBits);
};

void printImageHeader(BMPImageHeader_t imageHeader) {
   printf("Width: %d.\n", imageHeader.biWidth);
   printf("Height: %d.\n", imageHeader.biHeight);
   printf("Color Planes: %d.\n", imageHeader.biPlanes);
   printf("Bits per Pixel: %d.\n", imageHeader.biBitCount);
   printf("Compression: %d.\n", imageHeader.biCompression);
   printf("Image size: %d.\n", imageHeader.biSizeImage);
   printf("Preferred resolution in pixels per meter (X-Y): %d-%d.\n", imageHeader.biXPelsPerMeter, imageHeader.biYPelPerMeter);
   printf("Number color map: %d.\n", imageHeader.biClrUsed);
   printf("Number of significant colors: %d.\n", imageHeader.biClrImportant);
}
