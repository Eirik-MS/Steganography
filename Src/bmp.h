#ifndef BMP_H
#define BMP_H

#include <stdint.h>


typedef struct BmpFileHeader {
   char bfType[2];
   uint32_t bfSize;
   uint16_t __bfReserved1;
   uint16_t __bfReserved2;
   uint32_t bfOffBits;
} __attribute__ ((packed)) BMPFILEHEADER; 

typedef struct BmpImageHeader {
   unsigned int biSize;
   int biWidth;
   int biHeight;
   unsigned short int biPlanes;
   unsigned short int biBitCount;
   unsigned int biCompression;
   unsigned int biSizeImage;
   int biXPelsPerMeter;
   int biYPelPerMeter;
   unsigned int biClrUsed;
   unsigned int biClrImportant;  
} __attribute__ ((packed)) BMPIMAGEHEADER;


void printFileHeader(BMPFILEHEADER fileHeader);


void printImageHeader(BMPIMAGEHEADER imageHeader);


int read_bmp_headers(char * filepath);


#endif
