#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
Store all maze info
*/
typedef struct
{
    int start_position[2];
    int end_position[2];
    char *maze;
} MAZE;

typedef struct
{
    int current_pos_x;
    int current_pos_y;
} PLAYER;

/*
Module: to open the maze file and check whether it was opened properly.
The method takes in the file name and stores the maze into an array
realloc every time or read file twice
*/

int load_maze(maze)
{

    // Free the allocated memory before the pointer goes
}

/*
Function: Check if the maze is valid. Whether:
-The height and width are in a valid range
-There is a start point
-there is and end point
*/
int validate_maze(maze)
{
    // Check height & width range
}

/*
Function to update the values of the players current position in the maze
Parameters: player row position, player column position, the key that was pressed
*/

int update_move()
{
    // Check
    // return values of the player's current position
}

int main(int argc, char const *argv[])
{
    // Setup

    // display controls

    // Play
    // while the player has not made a bad move or has not yet won
        // player makes a move
        // Check whether the move that was valid
        // if it wasn't then display error message telling the player not to do that
        // Check if the player reached the exit point
        // Print winning message if they did & exithw
        // Exit the code
    return 0;
}
