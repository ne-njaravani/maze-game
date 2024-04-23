#ifndef MAZE_INIT_H
#define MAZE_INIT_H

#include <stdio.h>
#include <stdlib.h>

void create_maze(maze *this, int height, int width);
void free_maze(maze *this);
int get_width(FILE *file);
int get_height(FILE *file);
void read_maze(maze *this, FILE *file);

#endif // MAZE_INIT_H