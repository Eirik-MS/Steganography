#pragma once

/**
 * ----------------------------------------------------------------------------
 * @brief A List of strings with none helper variables \n
 * 
 * @details HAS NO HELPER FUNCTIONS (exept free_stringlist())
 */
typedef struct StringList{
    char **items;
    int count;
    int capacity;
} StringList_t;

/**
 * ----------------------------------------------------------------------------
 * @brief Frees all allocated data assosiated with the string list. 
 */
void free_stringlist(StringList_t * list);

/**
 * ----------------------------------------------------------------------------
 * @brief: Takes a directory and filename and constructs a full relative path
 *         to the given file. Allocates the reaulting string on the heap, 
 *         MUST BE FREED BY THE USER
 * 
 * @param: dir - a pointer to a string containing the foler path
 * @param: filename - a pointer to a string of the filename
 * 
 * @return: a pointer to the first char of the string (IE a string)
 * 
 */
char *build_filepath(const char *dir, const char *filename);
