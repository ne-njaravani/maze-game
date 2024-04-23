/**
 * @file maze.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief Main function to run the maze game
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MazeStructs.h"
#include "MazeConstants.h"
#include "FileManipulationFunctions.h"
#include "GameLogic.h"
#include "MazeInit.h"
#include "PlayerOperations.h"
#include "GameMessages.h"

/**
 * @brief Main function to run the maze game
 *
 * @param argc number of arguments
 * @param argv arguments
 * @return int return 0 if game is successful, or 1, 2, 3 on error
 */
int main(int argc, char const *argv[])
{
    // Setup
    coord *player = malloc(sizeof(coord));
    maze *this_maze = malloc(sizeof(maze));
    FILE *file;
    int win = 0;


    // Check args
    if (argc != 2)
    {
        printf("Usage: ./maze <mazefile path>\n");
        return CODE_ARG_ERROR;
    }
    else
    {
        // Open and validate mazefile
        // Check if the file is a valid file
        file = open_file(argv[1]);
    }

    // Get the maze dimensions
    this_maze->width = get_width(file);
    this_maze->height = get_height(file);

    // Initialise the maze and player
    create_maze(this_maze, this_maze->height, this_maze->width);
    read_maze(this_maze, file);
    welcome_message();
    initialise_player(player, this_maze);

    // Play the game
    while (win == 0)
    {
        win = game_loop(this_maze, player);
    }

    winner_message();

    // Clean up
    free_maze(this_maze);
    free_player(player);
    return CODE_SUCCESS;
}
