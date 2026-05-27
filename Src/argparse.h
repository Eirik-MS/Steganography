#pragma once

typedef struct {
    // 1 for distribute, 0 for recover
    int distribute; 

    char *image_name;

    int k;
    int n;

    char *filepath;
} ProgramOptions;

/**
 * @brief: Parses command-line arguments and populates a ProgramOptions struct with the provided values.
 * 
 * @param: argc - the count of command-line arguments
 * @param: argv - an array of strings representing the command-line arguments
 * @param: options - a pointer to a ProgramOptions struct to be populated with the parsed values
 * 
 * @return: 0 on success, or an error code if it encounters issues
 */
int argparse(int argc, char *argv[], ProgramOptions *options);

/**
 * @brief: Frees any dynamically allocated memory within the ProgramOptions struct.
 * @param: options - a pointer to a ProgramOptions struct whose allocated memory will be freed
 */
 void argparse_free(ProgramOptions *options);


