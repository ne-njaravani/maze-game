#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdio.h>
#include <stdlib.h>

int has_won(maze *this, coord *player);
int game_loop(maze *this_maze, coord *player);

#endif // GAME_LOGIC_H