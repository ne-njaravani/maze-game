/**
 * @file PlayerOperations.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief Functions to handle player operations
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
 * @brief Set the player's position to the start of the maze
 *
 * @param player the player's position
 * @param this the maze to use
 */
void initialise_player(coord *player, maze *this)
{
    player->x = this->start.x;
    player->y = this->start.y;
}

/**
 * @brief Free the memory allocated to the player struct
 *
 * @param player the pointer to the struct to free
 */
void free_player(coord *player)
{
    if (player != NULL)
    {
        free(player);
    }
}

/**
 * @brief Prints the maze out - code provided to ensure correct formatting
 *
 * @param this pointer to maze to print
 * @param player the current player location
 */
void print_maze(maze *this, coord *player)
{
    // make sure we have a leading newline..
    printf("\n");
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            // decide whether player is on this spot or not
            if (player->x == j && player->y == i)
            {
                printf("X");
            }
            else
            {
                printf("%c", this->map[i][j]);
            }
        }
        // end each row with a newline.
        printf("\n");
    }
}

/**
 * @brief Validates and makes a movement in a given direction or displays the map
 *
 * @param this Maze struct
 * @param player The player's current position
 * @param player_input The desired choice of the player
 * @return int 0 for invalid choice, 1 for valid choice
 */
int get_choice(maze *this, coord *player, char player_input)
{
    int new_x, new_y;
    char *direction[4] = {"UP", "DOWN", "LEFT", "RIGHT"};
    player_input = toupper(player_input);
    char *choice;

    // Check the player's choice
    switch (player_input)
    {
    case 'a':
    case 'A':
        new_x = player->x - 1;
        new_y = player->y;
        choice = direction[2];
        break;

    case 'd':
    case 'D':
        new_x = player->x + 1;
        new_y = player->y;
        choice = direction[3];
        break;

    case 'w':
    case 'W':
        new_x = player->x;
        new_y = player->y - 1;
        choice = direction[0];
        break;

    case 's':
    case 'S':
        new_x = player->x;
        new_y = player->y + 1;
        choice = direction[1];
        break;

    case 'm':
    case 'M':
        printf("\n...LOADING MAP...\n");
        print_maze(this, player);
        printf("\n");
        return 1;
        break;

    default:
        printf("Whoa! That input was invalid.\nLet's stick to the game's controls, shall we?\n");
        return 0;
        break;
    }

    // Check if the movement is in the boundaries of the maze
    if (new_x < 0 || new_x >= this->width || new_y < 0 || new_y >= this->height)
    {
        printf("Hold on, explorer! The secret to solving the maze is staying within its boundaries.\nLet's try another direction!\n");
        return 0;
    }

    if (this->map[new_y][new_x] == '#')
    {
        printf("Whoa there pal! You're no ghost, the walls are there for a reason!\nLet's stick to the open paths.\n");
        return 0;
    }
    else
    {
        player->x = new_x;
        player->y = new_y;
        printf("You have moved %s.\n", choice);
    }

    return 1;
}