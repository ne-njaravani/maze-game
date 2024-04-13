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
 * @return int 0 on success, 1 on fail
 */
int create_maze(maze *this, int height, int width)
{
    // allocate memory for height
    this->map = malloc(height * sizeof(char *));
    if (this->map == NULL)
    {
        return 1;
    }
    // allcocate memory for the width on each row
    for (int i = 0; i < height; i++)
    {
        this->map[i] = malloc(width * sizeof(char));
        if (this->map[i] == NULL)
        {
            return 1;
        }
    }
    return 0;
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
int get_width(FILE *file) {
    char line[MAX_DIM];
    if (fgets(line, MAX_DIM, file) == NULL) {
        return 0;
    }
    // Remove newline character from the line length calculation
    int file_width = strcspn(line, "\n");
    if (file_width < MIN_DIM || file_width > MAX_DIM) {
        return 0;
    }
    // Validate: whether each line is the same length as the first line
    int line_length;
    while (fgets(line, MAX_DIM, file) != NULL) {
        line_length = strcspn(line, "\n");
        if (line_length != file_width) {
            return 0;
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
int get_height(FILE *file) {
    int file_height = 0;
    char line[MAX_DIM];
    while (fgets(line, MAX_DIM, file) != NULL) {
        file_height++;
    }
    if (file_height < MIN_DIM || file_height > MAX_DIM) {
        return 0;
    }
    rewind(file);
    return file_height;
}

/**
 * @brief read in a maze file into a struct
 *
 * @param this Maze struct to be used
 * @param file Maze file pointer
 * @return int 0 on success, 1 on fail
 */
int read_maze(maze *this, FILE *file)
{
    int num_start = 0, num_end = 0;

    // read the maze into the struct
    for (int i = 0; i < this->height; i++)
    {
        if (fgets(this->map[i], this->width, file) == NULL)
        {
            return 1;
        }
        for (int j = 0; i < this->width; i++)
        {
            if (this->map[i][j] == 'S')
            {
                num_start++;
                this->start.x = i;
                this->start.y = j;
            }
            else if (this->map[i][j] == 'E')
            {
                num_end++;
                this->end.x = i;
                this->end.y = j;
            }
            else if (this->map[i][j] != ' ' && this->map[i][j] != '#' && this->map[i][j] != '\n')
            {
                return 1;
            }
        }
    }
    // Validate that each character in the array is either: ' ', 'S', 'E', '#' or '\n'
    // if the character is 'S' then increment num_start
    // if the character is 'E' then increment num_end
    // if the character is not any of the above then return 1
    // Validate that there is only one start and one end
    if (num_start != 1 && num_end != 1)
    {
        return 1;
    }

    // Validate that the start and end are not the same
    if (this->start.x == this->end.x && this->start.y == this->end.y)
    {
        return 1;
    }

    fclose(file);
    return 0;
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
 * @param direction The desired direction to move in
 * @return int 0 for invalid move, 1 for valid move
 */
int move(maze *this, coord *player, char direction)
{
    int new_x, new_y;

    // up movement
    if (direction == 'w' || direction == 'W')
    {
        new_x = player->x;
        new_y = player->y + 1;

        // Check if the movement is in the boundaries of the maze
        if (this->map[new_x][new_y] == '\n' || this->map[new_x][new_y] == '#' || new_x < 0 || new_x >= this->width || new_y < 0 || new_y >= this->height)
        {
            printf("W is an invalid move\n");
            return 0;
        }
        else
        {
            printf("You have moved up.\n");
            player->x = new_x;
            player->y = new_y;
        }
    }
    // left movement
    else if (direction == 'a' || direction == 'A')
    {
        new_x = player->x - 1;
        new_y = player->y;

        // Check if the movement is in the boundaries of the maze
        if (this->map[new_x][new_y] == '\n' || this->map[new_x][new_y] == '#' || new_x < 0 || new_x >= this->width || new_y < 0 || new_y >= this->height)
        {
            printf("A is an invalid move\n");
            return 0;
        }
        else
        {
            printf("You have moved left.\n");
            player->x = new_x;
            player->y = new_y;
        }
    }

    // down movement
    else if (direction == 's' || direction == 'S')
    {
        new_x = player->x;
        new_y = player->y - 1;

        // Check if the movement is in the boundaries of the maze
        if (this->map[new_x][new_y] == '\n' || this->map[new_x][new_y] == '#' || new_x < 0 || new_x >= this->width || new_y < 0 || new_y >= this->height)
        {
            printf("S is an invalid move\n");
            return 0;
        }
        else
        {
            printf("You have moved down.\n");
            player->x = new_x;
            player->y = new_y;
        }
    }

    // right movement
    else if (direction == 'd' || direction == 'D')
    {
        new_x = player->x + 1;
        new_y = player->y;

        // Check if the movement is in the boundaries of the maze
        if (this->map[new_x][new_y] == '\n' || this->map[new_x][new_y] == '#' || new_x < 0 || new_x >= this->width || new_y < 0 || new_y >= this->height)
        {
            printf("D is an invalid move\n");
            return 0;
        }
        else
        {
            printf("You have moved right.\n");
            player->x = new_x;
            player->y = new_y;
        }
    }

    else if (direction == 'm' || direction == 'M')
    {
        printf("Loading map...\n");
        print_maze(this, player);
    }

    else
    {
        printf("Invalid move\n");
        return 0;
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
    if (player->x == this->end.x && player->y == this->end.y && this->map[player->x][player->y] == 'E')
    {
        return 1;
    }
    return 0;
}
