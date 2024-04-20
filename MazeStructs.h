#ifndef MAZE_STRUCTS_H
#define MAZE_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

// Structure for the player's current position in the 2d array/ maze
typedef struct __Coord
{
    int x;
    int y;
} coord;

// Store maze info
typedef struct __Maze
{
    char **map;
    int height;
    int width;
    coord start;
    coord end;
} maze;


#endif // MAZE_STRUCTS_H