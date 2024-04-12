/**
 * @file maze.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief Code for the maze game
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// defines for max and min permitted dimensions
#define MAX_DIM 100
#define MIN_DIM 5

// defines for the required autograder exit codes
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3

// Structure for the player's current position in the 2d array/ maze
typedef struct __Coord
{
    int x;
    int y;
} coord;

// Store maze info
typedef struct __Maze
{
    char **map;
    int height;
    int width;
    coord start;
    coord end;
} maze;

// Adapted from Cbootcamp: Week 4 Session 1
FILE *open_file(char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: invalid file\n");
        exit(1); // Exits program with return status 1.
    }
}

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
    // set the height and width
    this->height = height;
    this->width = width;
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
int get_width(FILE *file)
{
    int file_width;
    char line[MAX_DIM];
    // read the width of the maze from the file.
    file_width = fgets(line, MAX_DIM, file);
    // Check if the initial line that was read was not null and whether it is a valid width
    if (file_width == NULL || file_width < MIN_DIM || file_width > MAX_DIM)
    {
        return 0;
    }
    // Validate: whether each line is the same length as the first line
    while (fgets(line, MAX_DIM, file) != NULL)
    {
        if (strlen(line) != file_width)
        {
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
int get_height(FILE *file)
{
    // check the height of each column in the mazefile
    int file_height;
    int line_width[get_width(file)];
    int file_pointer;
    char char_in_line;

    

    //if the width of the file was not valid then there's no need to check the height
    if (line_width == 0)
    {
        return 0;
    }
    else
    {
        // read the characters in a line
        for (int i = 0; i < line_width; i++)
        {
            // Move the file pointer to the ith character in the line
            file_pointer = fseek(file, i, SEEK_SET);
            {
                if (fseek != 0)
                {
                    return 0;
                }
            }
            
        }
        
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
 */
void move(maze *this, coord *player, char direction)
{
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
}

int main(int argc, char const *argv[])
{
    // Setup
    // Check args
    // Check if there's 2 args.
    // print usage error
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
