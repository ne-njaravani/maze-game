/**
 * @file MazeGenerator.c
 * @author Generated for maze-game
 * @brief Functions to auto-generate mazes using recursive backtracking algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MazeStructs.h"
#include "MazeConstants.h"
#include "MazeInit.h"
#include "MazeGenerator.h"

/**
 * @brief Shuffle an array of integers using Fisher-Yates algorithm
 *
 * @param arr array to shuffle
 * @param n size of array
 */
static void shuffle(int arr[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/**
 * @brief Recursive function to carve passages in the maze
 *
 * @param this pointer to the maze
 * @param x current x position (in grid coordinates)
 * @param y current y position (in grid coordinates)
 * @param grid_width width of the grid (passage cells)
 * @param grid_height height of the grid (passage cells)
 */
static void carve_passages(maze *this, int x, int y, int grid_width, int grid_height)
{
    // Directions: 0=up, 1=right, 2=down, 3=left
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    int directions[] = {0, 1, 2, 3};

    shuffle(directions, 4);

    for (int i = 0; i < 4; i++)
    {
        int dir = directions[i];
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // Check if the new cell is within bounds and unvisited (still a wall)
        if (nx >= 0 && nx < grid_width && ny >= 0 && ny < grid_height)
        {
            // Convert grid coordinates to map coordinates
            int map_nx = nx * 2 + 1;
            int map_ny = ny * 2 + 1;

            if (this->map[map_ny][map_nx] == '#')
            {
                // Carve the wall between current cell and new cell
                int wall_x = x * 2 + 1 + dx[dir];
                int wall_y = y * 2 + 1 + dy[dir];
                this->map[wall_y][wall_x] = ' ';

                // Carve the new cell
                this->map[map_ny][map_nx] = ' ';

                // Recurse
                carve_passages(this, nx, ny, grid_width, grid_height);
            }
        }
    }
}

/**
 * @brief Generate a random maze using recursive backtracking algorithm
 *
 * @param this pointer to the maze to generate
 * @param height desired height of the maze (5-100)
 * @param width desired width of the maze (5-100)
 */
void generate_maze(maze *this, int height, int width)
{
    // Validate dimensions
    if (height < MIN_DIM || height > MAX_DIM || width < MIN_DIM || width > MAX_DIM)
    {
        printf("Error: Invalid maze dimensions. Must be between %d and %d.\n", MIN_DIM, MAX_DIM);
        exit(CODE_MAZE_ERROR);
    }

    // Ensure dimensions are odd for proper maze structure
    if (height % 2 == 0)
        height++;
    if (width % 2 == 0)
        width++;

    // Cap at MAX_DIM
    if (height > MAX_DIM)
        height = MAX_DIM - 1;
    if (width > MAX_DIM)
        width = MAX_DIM - 1;

    // Set maze dimensions
    this->height = height;
    this->width = width;

    // Allocate memory for the maze
    create_maze(this, height, width);

    // Initialize all cells as walls
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            this->map[i][j] = '#';
        }
    }

    // Calculate grid dimensions (passage cells)
    int grid_width = (width - 1) / 2;
    int grid_height = (height - 1) / 2;

    // Start carving from position (0,0) - which is map position (1,1)
    this->map[1][1] = ' ';
    carve_passages(this, 0, 0, grid_width, grid_height);

    // Place start point at top-left area
    this->start.x = 1;
    this->start.y = 1;
    this->map[1][1] = 'S';

    // Place end point at bottom-right area (find a valid position)
    int end_x = -1, end_y = -1;
    for (int i = height - 2; i >= 1; i--)
    {
        for (int j = width - 2; j >= 1; j--)
        {
            if (this->map[i][j] == ' ')
            {
                end_x = j;
                end_y = i;
                break;
            }
        }
        if (end_x != -1)
            break;
    }

    if (end_x != -1 && end_y != -1)
    {
        this->end.x = end_x;
        this->end.y = end_y;
        this->map[end_y][end_x] = 'E';
    }
    else
    {
        // Fallback: place end at a known carved position
        this->end.x = width - 2;
        this->end.y = height - 2;
        this->map[height - 2][width - 2] = 'E';
    }

    printf("Maze generated successfully!\n");
}
