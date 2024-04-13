#include <stdio.h>
#include <stdlib.h>

static FILE *open_file(char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: invalid file\n");
        exit(1); // Exits program with return status 1.
    }
}

const char* get_filename_from_path(const char* path)
{
    // strrchr returns a pointer to the last occurrence of a character in a string.
    // This was adapted from: 
    // https://stackoverflow.com/questions/24975928/extract-the-file-name-and-its-extension-in-c
    // https://www.geeksforgeeks.org/strrchr-in-c/
    const char* last_slash = strrchr(path, '/');
    if (last_slash != NULL)
    {
        return last_slash + 1;
    }
    else
    {
        return path;
    }
}