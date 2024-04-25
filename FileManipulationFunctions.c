/**
 * @file FileManipulationFunctions.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief File manipulation functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MazeConstants.h"
#include "FileManipulationFunctions.h"

/**
 * @brief Open a file and return a pointer to it
 *
 * @param filename the name of the file to open
 * @return FILE* the pointer to the file
 */
FILE *open_file(const char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: invalid file\n");
        exit(CODE_FILE_ERROR); // Exits program with return status 1.
    }
    return file;
}

const char *get_filename_from_path(const char *path)
{
    // strrchr returns a pointer to the last occurrence of a character in a string.
    // This was adapted from:
    // https://stackoverflow.com/questions/24975928/extract-the-file-name-and-its-extension-in-c
    // https://www.geeksforgeeks.org/strrchr-in-c/
    const char *last_slash = strrchr(path, '/');
    if (last_slash != NULL)
    {
        return last_slash + 1;
    }
    else
    {
        printf("File name: %s\n", path);
        return path;
    }
}