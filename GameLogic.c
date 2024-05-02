/**
 * @file GameLogic.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief Functions for the logic of the maze game
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
 * @brief Check whether the player has won i.e. reached the end-point of the maze
 *
 * @param this current maze
 * @param player player position
 * @return int 0 for false, 1 for true
 */
int has_won(maze *this, coord *player)
{
    if (player->x == this->end.x && player->y == this->end.y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief Get the player's choice and their position in the maze accordingly or display the map
 *
 * @param this_maze the maze to update or display
 * @param player the player's position
 * @param choice the player's choice
 * @return int 0 for invalid choice, 1 for valid choice
 */
int game_loop(maze *this_maze, coord *player)
{
    int valid_choice;
    char player_choice[3];

    do
    {
        controls_message();
        printf("Enter your choice: ");

        // Read up to 2 characters and \n
        // This concept was adapted from:
        // https://stackoverflow.com/questions/4023895/how-to-read-string-entered-by-user-in-c
        fgets(player_choice, 3, stdin);

        // Check for newline character
        if (strchr(player_choice, '\n') != NULL)
        {
            player_choice[strcspn(player_choice, "\n")] = '\0';

            // Check if input is exactly 1 character
            if (strlen(player_choice) == 1)
            {
                valid_choice = get_choice(this_maze, player, player_choice[0]);
            }
            else
            {
                printf("\nI see you've entered an invisible character...."
                       "\nLet's try entering a visible one, shall we?\n");
                valid_choice = 0;
            }
        }
        else
        {
            printf("\nWhoa there mate!\nJust one character will do the trick.\n");
            while (getchar() != '\n')
                // Clear the input buffer
            
            valid_choice = 0;
        }
    } while (valid_choice == 0);
    return has_won(this_maze, player);
}