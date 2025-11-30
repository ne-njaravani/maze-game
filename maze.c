/**
 * @file maze.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief Main function to run the maze game
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "MazeStructs.h"
#include "MazeConstants.h"
#include "FileManipulationFunctions.h"
#include "GameLogic.h"
#include "MazeInit.h"
#include "PlayerOperations.h"
#include "GameMessages.h"
#include "MazeGenerator.h"

/**
 * @brief Prompt user to choose between premade or auto-generated maze
 *
 * @return int 1 for premade, 2 for auto-generate
 */
int get_maze_choice(void)
{
    char choice[3];
    int valid = 0;

    while (!valid)
    {
        printf("\n=== MAZE GAME ===\n");
        printf("Choose your maze option:\n");
        printf("1. Load a premade maze from file\n");
        printf("2. Auto-generate a new maze\n");
        printf("Enter your choice (1 or 2): ");

        if (fgets(choice, 3, stdin) != NULL)
        {
            // Check for newline character
            if (strchr(choice, '\n') != NULL)
            {
                choice[strcspn(choice, "\n")] = '\0';

                if (strlen(choice) == 1)
                {
                    if (choice[0] == '1')
                    {
                        return 1;
                    }
                    else if (choice[0] == '2')
                    {
                        return 2;
                    }
                    else
                    {
                        printf("Invalid choice. Please enter 1 or 2.\n");
                    }
                }
                else
                {
                    printf("Invalid input. Please enter only 1 or 2.\n");
                }
            }
            else
            {
                printf("Input too long. Please enter only 1 or 2.\n");
                while (getchar() != '\n')
                    ; // Clear input buffer
            }
        }
    }
    return 1; // Default to premade
}

/**
 * @brief Get maze dimensions from user for auto-generation
 *
 * @param height pointer to store height
 * @param width pointer to store width
 */
void get_maze_dimensions(int *height, int *width)
{
    char input[10];

    printf("\nEnter maze dimensions (between %d and %d):\n", MIN_DIM, MAX_DIM);

    // Get width
    printf("Width: ");
    if (fgets(input, 10, stdin) != NULL)
    {
        *width = atoi(input);
        if (*width < MIN_DIM)
            *width = MIN_DIM;
        if (*width > MAX_DIM)
            *width = MAX_DIM;
    }
    else
    {
        *width = 15; // Default
    }

    // Get height
    printf("Height: ");
    if (fgets(input, 10, stdin) != NULL)
    {
        *height = atoi(input);
        if (*height < MIN_DIM)
            *height = MIN_DIM;
        if (*height > MAX_DIM)
            *height = MAX_DIM;
    }
    else
    {
        *height = 15; // Default
    }
}

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
    int maze_choice;
    int maze_height, maze_width;

    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Prompt user for maze choice
    maze_choice = get_maze_choice();

    if (maze_choice == 1)
    {
        // Load premade maze from file
        // Check args
        if (argc != 2)
        {
            printf("Usage: ./maze <mazefile path>\n");
            free(player);
            free(this_maze);
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
    }
    else
    {
        // Auto-generate maze
        get_maze_dimensions(&maze_height, &maze_width);
        generate_maze(this_maze, maze_height, maze_width);
    }

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
