#include <stdio.h>
#include <stdlib.h>


#include "env.h"
#include "bmp.h"

int read_bmp_headers(char * filepath, BMPImage_t *image){
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


void bmp_image_free(BMPImage_t *image) {
    if (image->pixel) {
        free(image->pixel);
        image->pixel = NULL;
    }
    if (image->colorTab) {
        free(image->colorTab);
        image->colorTab = NULL;
    }
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
