/**
 * @file MazeFunctions.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief Functions for the maze game
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MazeStructs.h"
#include "MazeConstants.h"
#include "FileManipulationFunctions.h"
#include "MazeFunctions.h"

/**
 * @brief Initialise a maze object - allocate memory and set attributes
 *
 * @param this pointer to the maze to be initialised
 * @param height height to allocate
 * @param width width to allocate
 * @return int 1 on success, 0 on fail
 */
void create_maze(maze *this, int height, int width)
{
    // allocate memory for height
    this->map = malloc(height * sizeof(char *));
    if (this->map == NULL)
    {
        printf("Error: Memory allocation for the number of rows failed\n");
        exit(CODE_MAZE_ERROR);
    }
    // allcocate memory for the width on each row
    for (int i = 0; i < height; i++)
    {
        this->map[i] = malloc(width * sizeof(char));
        if (this->map[i] == NULL)
        {
            printf("Error: Memory allocation for width on each row failed\n");
            exit(CODE_MAZE_ERROR);
        }
    }
}

/**
 * @brief Free the memory allocated to the maze struct
 *
 * @param this the pointer to the struct to free
 */
void free_maze(maze *this)
{
    // free each row of the map
    for (int i = 0; i < this->height; i++)
    {
        free(this->map[i]);
    }
}

/**
 * @brief Validate and return the width of the mazefile
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid width (5-100)
 */
int get_width(FILE *file)
{
    rewind(file);
    char line[MAX_DIM];
    if (fgets(line, MAX_DIM, file) == NULL)
    {
        printf("Invalid maze width: no width found\n");
        exit(CODE_MAZE_ERROR);
    }
    // Remove newline character from the line length calculation
    int file_width = strcspn(line, "\n");
    if (file_width < MIN_DIM)
    {
        printf("Invalid maze width: too narrow\n");
        exit(CODE_MAZE_ERROR);
    }
    if (file_width > MAX_DIM)
    {
        printf("Invalid maze width: too wide\n");
        exit(CODE_MAZE_ERROR);
    }
    // Validate: whether each line is the same length as the first line
    int line_length;
    while (fgets(line, MAX_DIM, file) != NULL)
    {
        line_length = strcspn(line, "\n");
        if (line_length != file_width)
        {
            printf("Invalid maze width: inconsistent line length\n");
            exit(CODE_MAZE_ERROR);
        }
    }
    rewind(file);
    return file_width;
}

/**
 * @brief Validate and return the height of the mazefile
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid height (5-100)
 */
int get_height(FILE *file)
{
    rewind(file);
    int file_height = 0;
    char line[MAX_DIM];
    while (fgets(line, MAX_DIM, file) != NULL)
    {
        file_height++;
    }
    if (file_height < MIN_DIM)
    {
        printf("Invalid maze height: too short\n");
        exit(CODE_MAZE_ERROR);
    }
    if (file_height > MAX_DIM)
    {
        printf("Invalid maze height: too long\n");
        exit(CODE_MAZE_ERROR);
    }
    rewind(file);
    return file_height;
}

/**
 * @brief read in a maze file into a struct
 *
 * @param this Maze struct to be used
 * @param file Maze file pointer
 * @return int 1 on success, 0 on fail
 */
void read_maze(maze *this, FILE *file)
{
    int num_start = 0;
    int num_end = 0;
    int i = 0;
    int j = 0;
    rewind(file);

    // read the maze into the struct
    char ch;

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch != '\n')
        {
            this->map[i][j] = ch;

            // Check if the character is 'S' or 'E'
            if (ch == 'S')
            {
                this->start.x = j;
                this->start.y = i;
                num_start++;
            }
            if (ch == 'E')
            {
                this->end.x = j;
                this->end.y = i;
                num_end++;
            }

            j++;
            if (j == this->width)
            {
                j = 0;
                i++;
            }
        }
    }

    // Validate that the only characters in the maze are '#', 'S', 'E', and ' '
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (this->map[i][j] != '#' && this->map[i][j] != 'S' && this->map[i][j] != 'E' && this->map[i][j] != ' ')
            {
                printf("Error: Invalid character in maze\n");
                free_maze(this);
                exit(CODE_MAZE_ERROR);
            }
        }
    }

    // Validate that there is only one start and end point
    if (num_start < 1)
    {
        printf("Error: No start point found\n");
        free_maze(this);
        exit(CODE_MAZE_ERROR);
    }
    else if (num_start > 1)
    {
        printf("Error: More than one start point found\n");
        free_maze(this);
        exit(CODE_MAZE_ERROR);
    }    


    if (num_end < 1)
    {
        printf("Error: No end point found\n");
        free_maze(this);
        exit(CODE_MAZE_ERROR);
    }
    else if (num_end > 1)
    {
        printf("Error: More than one end point found\n");
        free_maze(this);
        exit(CODE_MAZE_ERROR);
    }

    printf("Maze loaded successfully!\n");
    fclose(file);
}

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
 * @brief Validates and makes a movement in a given direction
 *
 * @param this Maze struct
 * @param player The player's current position
 * @param player_input The desired direction to move in
 * @return int 0 for invalid move, 1 for valid move
 */
int move(maze *this, coord *player, char player_input)
{
    int new_x, new_y;
    char *direction[4] = {"UP", "DOWN", "LEFT", "RIGHT"};
    player_input = toupper(player_input);
    char *move;

    switch (player_input)
    {
    case 'a':
    case 'A':
        new_x = player->x - 1;
        new_y = player->y;
        move = direction[2];
        break;

    case 'd':
    case 'D':
        new_x = player->x + 1;
        new_y = player->y;
        move = direction[3];
        break;

    case 'w':
    case 'W':
        new_x = player->x;
        new_y = player->y - 1;
        move = direction[0];
        break;

    case 's':
    case 'S':
        new_x = player->x;
        new_y = player->y + 1;
        move = direction[1];
        break;

    case 'm':
    case 'M':
        printf("\nLoading map...\n");
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
        printf("Oops! Trying to phase through walls? You're not The Flash!\nLet's stick to the open paths.\n");
        return 0;
    }
    else
    {
        player->x = new_x;
        player->y = new_y;
         printf("You have moved %s.\n", move);
    }

    return 1;
}

/**
 * @brief Check whether the player has won and return a pseudo-boolean
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
