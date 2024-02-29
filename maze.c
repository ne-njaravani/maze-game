#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Store information of the maze
typedef struct
{
    int start_position[2];
    int end_position[2];
    char *maze;
} MAZE;

// Structure for the player's current position in the 2d array/ maze
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
    /*Allocate memory to the array which will store the maze
    Read the data from the file if it was successfully opened.
    Free the allocated memory before the pointer goes
    return true if the maze was successfully opened. False otherwise
    */
}

/*
Function: Check if the maze is valid. Whether:
-The height and width are in a valid range
-There is a start point
-there is and end point
*/
int validate_maze(maze)
{
    // Check whether the height and width are within an acceptable range
    // Check for the presence of a starting point and an end point in the maze
        // Ensure that there is only 1 of each.
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
ss
int display_maze(char move)
{
    // Check if the move is m/M
    // Using the player's current position, check where they are in the maze
    // Create a copy of the maze and replace the char in the maze with x
    // Print the maze copy
}

int main(int argc, char const *argv[])
{
    // Setup
        // Check if theer's 2 args.
            // print usage error 

    // display controls to user

    // Play
    // while the player has not made a bad move or has not yet won
        // player makes a move
            // Check whether the move that was valid
                // if it wasn't then display error message telling the player not to do that
        // Check if the player reached the exit point
            // Print winning message if they did & exit the code
    return 0;
}
