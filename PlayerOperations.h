#ifndef PLAYER_OPERATIONS_H
#define PLAYER_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>

// Maze function prototypes
void initialise_player(coord *player, maze *this);
void print_maze(maze *this, coord *player);
int get_choice(maze *this, coord *player, char player_input);
void free_player(coord *player);

#endif // PLAYER_OPERATIONS_H