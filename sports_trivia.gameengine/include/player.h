#ifndef PLAYER_H
#define PLAYER_H

#define PLAYERNAME_MAXLENGTH 15

char player1Name[PLAYERNAME_MAXLENGTH+1];
char player2Name[PLAYERNAME_MAXLENGTH+1];
unsigned int player1Score;
unsigned int player2Score;

void initializePlayersData();

char *getPlayerScoreAsString(unsigned int score);

#endif