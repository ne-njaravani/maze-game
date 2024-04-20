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
    char welcome_message[] = "\n \\ \\        /  ____|  |       ___|   _ \\    \\  |  ____|      __ __|  _ \\ "
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
                             "\n \\____| _/    _\\ _|  _| _____| _) _)                                     ";

    char winner_message[] = "\n     \\            \\  |     \\    __  / _ _|   \\  |   ___|  |  |  |       "
                            "\n    _ \\          |\\/ |    _ \\      /    |     \\ |  |      |  |  |       "
                            "\n   ___ \\ _____|  |   |   ___ \\    /     |   |\\  |  |   | _| _| _|       "
                            "\n _/    _\\       _|  _| _/    _\\ ____| ___| _| \\_| \\____| _) _) _)       "
                            "\n\n \\ \\   /  _ \\   |   |  ) \\ \\     /  ____|      \\ \\        /  _ \\    \\  |"
                            "\n  \\   /  |   |  |   | /   \\ \\   /   __|         \\ \\  \\   /  |   |    \\ |"
                            "\n     |   |   |  |   |      \\ \\ /    |            \\ \\  \\ /   |   |  |\\  |"
                            "\n    _|  \\___/  \\___/        \\_/    _____|         \\_/\\_/   \\___/  _| \\_|"
                            "\n\n __ __|  |   |  ____|        ___|     \\     \\   |  ____|  |  |          "
                            "\n    |    |   |  __|         |        _ \\    |\\/ |  __|    |  |          "
                            "\n    |    ___ |  |           |   |   ___ \\   |   |  |     _| _|          "
                            "\n   _|   _|  _| _____|      \\____| _/    _\\ _|  _| _____| _) _)          ";

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

    printf("%s\n", welcome_message);

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
        scanf(" %c", &player_move);
        printf("Player entered %c\n", player_move);
        player_move = toupper(player_move);
        valid_move = move(this_maze, player, player_move);
        // Keep asking for a move until a valid move is made
        while (valid_move == 0)
        {
            printf("Invalid move. Try again.\n");
            scanf(" %c", &player_move);
            player_move = toupper(player_move);
            valid_move = move(this_maze, player, player_move);
            printf("Valid move: %d\n", valid_move);
        }
        win = has_won(this_maze, player);
    }

    printf("A-MAZING!!! You have won the game!\n");
    free_maze(this_maze);
    return CODE_SUCCESS;
    // return, free, exit
}
