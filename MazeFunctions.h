#ifndef MAZE_FUNCTIONS_H
#define MAZE_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

// Maze function prototypes 
void create_maze(maze *this, int height, int width);
void free_maze(maze *this);
void free_player(coord *player);
int get_width(FILE *file);
int get_height(FILE *file);
void read_maze(maze *this, FILE *file);
void initialise_player(coord *player, maze *this);
void print_maze(maze *this, coord *player);
int get_choice(maze *this, coord *player, char player_input);
int has_won(maze *this, coord *player);
int game_loop(maze *this_maze, coord *player);

#endif // MAZE_FUNCTIONS_H