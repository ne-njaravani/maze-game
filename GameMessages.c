/**
 * @file MazeInit.c
 * @author Ngakudzweishe E. (Eben) Njaravani
 * @brief Functions to print the controls and ascii art messages
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
 * @brief Print the welcome message
 */
void welcome_message()
{
    printf("\n\n \\ \\        /  ____|  |       ___|   _ \\    \\  |  ____|      __ __|  _ \\ "
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
           "\n\nReady for an adventure? Let's go!\n\n");
}

/**
 * @brief Print the winner message
 */
void winner_message()
{
    printf("\n\n     \\            \\  |     \\    __  / _ _|   \\  |   ___|  |  |  |       "
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
           "\n   _|   _|  _| _____|      \\____| _/    _\\ _|  _| _____| _) _)          \n\n");
}

void controls_message()
{
    printf("\n\nHere's your control guide:\n"
           "\tW - Move up\n"
           "\tA - Move left\n"
           "\tS - Move down\n"
           "\tD - Move right\n"
           "\tM - Display the map\n\n");
}