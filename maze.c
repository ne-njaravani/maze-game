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
    coord *player = malloc(sizeof(coord));
    maze *this_maze = malloc(sizeof(maze));
    FILE *file;
    int valid_read, valid_create, valid_move;
    int win = 0;
    char player_move;
    const char *controls = "\n Use the following controls to move the player:\n"
                           "W - Move up\n"
                           "A - Move left\n"
                           "S - Move down\n"
                           "D - Move right\n"
                           "M - Display the map\n"
                           "Make your move: ";

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
        file = open_file(argv[1]);
    }

    printf("Welcome to the Maze Game\n");

    // Read in maze file to struct
    this_maze->width = get_width(file);
    this_maze->height = get_height(file);


    valid_create = create_maze(this_maze, this_maze->height, this_maze->width);

    rewind(file);
    valid_read = read_maze(this_maze, file);


    initialise_player(player, this_maze);

    // Play (maze game loop)
    while (win == 0)
    {
        printf("%s", controls);
        scanf(" %c", &player_move);
        player_move = toupper(player_move);
        valid_move = move(this_maze, player, player_move);
        // Keep asking for a move until a valid move is made
        while (valid_move == 0)
        {
            printf("Invalid move. Try again.\n");
            printf(" %s", controls);
            scanf(" %c", &player_move);
            player_move = toupper(player_move);
            valid_move = move(this_maze, player, player_move);
        }
        win = has_won(this_maze, player);
    }

    printf("A-MAZING!!! You have won the game!\n");
    free_maze(this_maze);
    return CODE_SUCCESS;
    // return, free, exit
}
