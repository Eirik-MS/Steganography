#pragma once

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


/**
 * @brief: Searches thru a directory to find all bmp files and then attempts to read
 *         the header ot verify that the file is a bitmap  
 * 
 * @param: filepath - a pointer to a string containing the path to the BMP file
 * 
 * @return: Pointer to a List of Strings of all the bmp files that it could find in the directory
 */
StringList_t *find_validate_bmp_files(char * filepath);

/**
 * @brief: Takes a file path to a BMP image and a pointer to a BMPImage_t struct. 
 *        Populating the BMPImage_t struct with the data from the image found at the filepath. 
 *        The function returns 0 on success, or an error code if it encounters issues.
 * 
 * @param: filepath - a pointer to a string containing the path to the BMP file
 * @param: image - a pointer to a BMPImage_t struct to be populated with the image data
 * 
 * @return: 0 on success, or an error code if it encounters issues
 */
int read_bmp_file(char * filepath, BMPImage_t *image);

/**
 *-----------------------------------------------------
 * @brief: Frees the memory allocated for the image.
 * @param: image - a pointer to a BMPImage_t struct whose allocated memory will be freed
 */
void free_bmp_img(BMPImage_t *image);

/**
 * @brief Create and write a bmp image to disk
 * 
 * @param : image - a pointer to a BMPImage_t struct containing the data for the image
 * @param: filepath - a string representing the path where the bmp image will be written
 * @param: filename - a string representing the name of the file that will be created
 * 
 * @return: 1 on sucsess
 */
int write_bmp_file(BMPImage_t *image, char *filepath, char *filename);

void printFileHeader(BMPFileHeader_t fileHeader);
void printImageHeader(BMPImageHeader_t imageHeader);
