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



int main(int argc, char const *argv[])
{
    // Setup
    coord *player;
    maze *this_maze = malloc(sizeof(maze));
    FILE *file;
    int win = 0;
    const char* file_name;

        // Check args
        if (argc != 2)
        {
            printf("./maze <mazefile path>\n");
            return CODE_ARG_ERROR;
        }
        else
        {
            // Open and validate mazefile
            // Check if the file is a valid file
            file_name = get_filename_from_path(argv[1]);
            FILE *file = open_file(file_name);

            if (file == NULL)
            {
                return CODE_FILE_ERROR;
            }
        }

        printf("Welcome to the Maze Game\n");
    
        // Read in maze file to struct
        this_maze->width = get_width(file);
        this_maze->height = get_height(file);

        if (this_maze->width == 0 || this_maze->height == 0)
        {
            return CODE_MAZE_ERROR;
        }
        
        

    


    // read in maze file to struct

    // Play (maze game loop)
    while (win == 0)
    {
        
    }
    
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



    return CODE_SUCCESS;
    // return, free, exit
}
