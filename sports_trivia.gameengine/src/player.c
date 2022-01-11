#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializePlayersData()
{
    strcpy(player1Name, "");
    strcpy(player2Name, "");
    player1Score = 0;
    player2Score = 0;
}

char *getPlayerScoreAsString(unsigned int score)
{
    char *retVal = malloc(10 * sizeof(char));
    sprintf(retVal, "%u", score);
    return retVal;
}