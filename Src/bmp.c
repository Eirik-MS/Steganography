#include <stdio.h>
#include <stdlib.h>


#include "bmp.h"

int read_bmp_headers(char * filepath){
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filepath);
        return -1;
    }
    
    BMPFILEHEADER fileHeader;
    BMPIMAGEHEADER imageHeader;
    
    fread(&fileHeader, sizeof(BMPFILEHEADER), 1, file);
    fread(&imageHeader, sizeof(BMPIMAGEHEADER), 1, file);
    
    printFileHeader(fileHeader);
    printImageHeader(imageHeader);
    
    fclose(file);
    return 0;
}


void printFileHeader(BMPFILEHEADER fileHeader) {
   printf("\nType: %c%c.\n", fileHeader.bfType[0],fileHeader.bfType[1]);
   printf("Size: %d.\n", fileHeader.bfSize);
   printf("Verify (Must be 0 0): %d %d.\n" ,fileHeader.__bfReserved1, fileHeader.__bfReserved2);
   printf("Offset : %d.\n", fileHeader.bfOffBits);
};

void printImageHeader(BMPIMAGEHEADER imageHeader) {
   printf("\nSize of header: %d.\n", imageHeader.biSize);
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
