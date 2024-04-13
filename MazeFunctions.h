#ifndef MAZE_FUNCTIONS_H
#define MAZE_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

// Maze function prototypes 
int create_maze(maze *this, int height, int width);
void free_maze(maze *this);
int get_width(FILE *file);
int get_height(FILE *file);
int read_maze(maze *this, FILE *file);
void initialise_player(coord *player, maze *this);
void print_maze(maze *this, coord *player);
int move(maze *this, coord *player, char direction);
int has_won(maze *this, coord *player);

#endif // MAZE_FUNCTIONS_H