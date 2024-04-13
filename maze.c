/**
 * @file maze.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief Code for the maze game
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MazeStructs.h"
#include "MazeConstants.h"
#include "FileManipulationFunctions.h"
#include "MazeFunctions.h"


FILE *open_file(char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: invalid file\n");
        exit(CODE_FILE_ERROR); // Exits program with return status 1.
    }
}

int main(int argc, char const *argv[])
{
    // Setup

        // Check args
        if (argc != 2)
        {
            printf("./maze <mazefile path>\n");
            return CODE_ARG_ERROR;
        }
        else
        {
            // Check if the file is a valid file
            FILE *file = open_file(argv[1]);
            if (file == NULL)
            {
                return CODE_FILE_ERROR;
            }
        }
        
            // Setup useful variables
    coord *player;
    maze *this_maze = malloc(sizeof(maze));
    FILE *file;
    int width, height, win;

    // display controls to user

    // Open and validate mazefile

    // read in maze file to struct

    // Play (maze game loop)
        // while the player has not made a bad move or has not yet won
            // player makes a move
                // Check whether the move that was valid
                    // if it was
                        // then update the player's position
                    // if it wasn't
                        // then display error message telling the player not to do that
                // Check if the player reached the exit point
                    // Print winning message if they did & exit the code

    // Win

    // return, free, exit
}
