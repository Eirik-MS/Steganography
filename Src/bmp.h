#ifndef BMP_H
#define BMP_H

#include <stdint.h>


typedef struct BmpFileHeader {
   char bfType[2];
   uint32_t bfSize;
   uint16_t __bfReserved1;
   uint16_t __bfReserved2;
   uint32_t pxOffsetBits;
} __attribute__ ((packed)) BMPFileHeader_t; 

typedef struct BmpImageHeader {
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;  
} __attribute__ ((packed)) BMPImageHeader_t;

typedef struct {
    BMPFileHeader_t     fileHeader;        // fixed 14-byte array on the stack
    BMPImageHeader_t    infoHeader;       // heap-allocated, variable size
    uint32_t            infoHeaderSize;
    unsigned char       *colorTab;         // heap-allocated, NULL if absent
    int                 colorTabSize;
    int32_t             width, height;     // extracted for convenient access
    unsigned char       *pixel;            // heap-allocated pixel buffer
} BMPImage_t;

void printFileHeader(BMPFileHeader_t fileHeader);
void printImageHeader(BMPImageHeader_t imageHeader);


int read_bmp_headers(char * filepath, BMPImage_t *image);

void bmp_image_free(BMPImage_t *image);


#endif
