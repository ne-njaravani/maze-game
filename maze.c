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
    int win = 0;
    char welcome_message[] = "\n\n \\ \\        /  ____|  |       ___|   _ \\    \\  |  ____|      __ __|  _ \\ "
                             "\n  \\ \\  \\   /   __|    |      |      |   |  |\\/ |  __|           |   |   |"
                             "\n   \\ \\  \\ /    |      |      |      |   |  |   |  |             |   |   |"
                             "\n    \\_/\\_/    _____| _____| \\____| \\___/  _|  _| _____|        _|  \\___/ "
                             "\n\n __ __|  |   |  ____|        \\  |     \\    __  /  ____|                  "
                             "\n    |    |   |  __|         |\\/ |    _ \\      /   __|                    "
                             "\n    |    ___ |  |           |   |   ___ \\    /    |                      "
                             "\n   _|   _|  _| _____|      _|  _| _/    _\\ ____| _____|                  "
                             "\n\n   ___|     \\      \\  |  ____|  |  |                                     "
                             "\n  |  __    _ \\    |\\/ |  __|    |  |                                     "
                             "\n  |   |   ___ \\   |   |  |     _| _|                                     "
                             "\n \\____| _/    _\\ _|  _| _____| _) _)                                     \n\n"
                             "\n\nWelcome to the maze game! Your goal is to navigate through the maze and reach the end.\n"
                             "\n\nReady for an adventure? Let's go!\n\n";

    char winner_message[] = "\n\n     \\            \\  |     \\    __  / _ _|   \\  |   ___|  |  |  |       "
                            "\n    _ \\          |\\/ |    _ \\      /    |     \\ |  |  __  |  |  |       "
                            "\n   ___ \\ _____|  |   |   ___ \\    /     |   |\\  |  |   | _| _| _|       "
                            "\n _/    _\\       _|  _| _/    _\\ ____| ___| _| \\_| \\____| _) _) _) (Yes pun intended)      "
                            "\n\n \\ \\   /  _ \\   |   |  ) \\ \\     /  ____|      \\ \\        /  _ \\    \\  |"
                            "\n  \\   /  |   |  |   | /   \\ \\   /   __|         \\ \\  \\   /  |   |    \\ |"
                            "\n     |   |   |  |   |      \\ \\ /    |            \\ \\  \\ /   |   |  |\\  |"
                            "\n    _|  \\___/  \\___/        \\_/    _____|         \\_/\\_/   \\___/  _| \\_|"
                            "\n\n __ __|  |   |  ____|        ___|     \\     \\   |  ____|  |  |          "
                            "\n    |    |   |  __|         |  __    _ \\    |\\/ |  __|    |  |          "
                            "\n    |    ___ |  |           |   |   ___ \\   |   |  |     _| _|          "
                            "\n   _|   _|  _| _____|      \\____| _/    _\\ _|  _| _____| _) _)          \n\n";



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

    // Read in maze file to struct
    this_maze->width = get_width(file);
    this_maze->height = get_height(file);

    create_maze(this_maze, this_maze->height, this_maze->width);

    read_maze(this_maze, file);

    printf("\n%s\n", welcome_message);

    initialise_player(player, this_maze);

    // Play (maze game loop)
    while (win == 0)
    {
        win = game_loop(this_maze, player);
    }

    printf("\n%s\n", winner_message);
    free_maze(this_maze);
    free(player);
    return CODE_SUCCESS;
    // return, free, exit
}
