/**
 * @file MazeInit.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief Functions to initialise the maze to be used in the game
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
 * @brief Initialise a maze object - allocate memory and set attributes (Remember to free)
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
            // free the memory allocated so far
            for (int j = 0; j < i; j++)
            {
                free(this->map[j]);
            }
            free(this->map);
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
    if (this != NULL)
    {
        // free the rows in the map
        for (int i = 0; i < this->height; i++)
        {
            free(this->map[i]);
        }
        free(this->map);
        // free the struct
        free(this);
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

    // Validate that there is only one start and end point in the maze

    if (num_start < 1)
    {
        printf("Error: No start point found\n");
        free_maze(this);
        exit(CODE_MAZE_ERROR);
    }
    else if (num_start > 1)
    {
        printf("Error: More than 1 start point found\n");
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
        printf("Error: More than 1 end point found\n");
        free_maze(this);
        exit(CODE_MAZE_ERROR);
    }

    printf("Maze loaded successfully!\n");
    fclose(file);
}