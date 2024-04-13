#ifndef FILE_MANIPULATION_FUNCTIONS_H
#define FILE_MANIPULATION_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Adapted from Cbootcamp: Week 4 Session 1
FILE *open_file(const char filename[]);

const char* get_filename_from_path(const char* path);

#endif // FILE_MANIPULATION_FUNCTIONS_H