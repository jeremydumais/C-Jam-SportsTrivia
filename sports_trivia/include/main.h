#ifndef MAIN_H
#define MAIN_H

#include "gamewindow.h"
#include "label.h"
#include "player.h"

typedef enum { titleScreen, 
              enterPlayer1Name, 
              enterPlayer2Name, 
              playGame, 
              endGame } GameMode;

GameMode currentGameMode = titleScreen;
InputMode currentInputMode = NoInput;

//Text input objets
char *currentInput = NULL;
int currentInputMaxLength = 0;
LabelObj *currentInputTextObj = NULL;
bool currentInputNeedToRerender = true;

//Number choice objects
unsigned int currentChoiceMin = 0;
unsigned int currentChoiceMax = 0;
unsigned int *currentChoiceResult = NULL;

bool quit = false;

//Graphical objects
SDL_Event event;
SDL_Window *window = NULL;
int windowWidth = 0;
int windowXCenter = 0;
SDL_Renderer *renderer = NULL;

typedef struct {
    SDL_Texture **texture;
    const char *filePath;
} InitTextureObj;
SDL_Texture *backgroundTexture = NULL;
SDL_Texture *backgroundTextureTitle = NULL;
SDL_Texture *scoreboardTexture = NULL;

bool initializeSDL();
void destroySDL();

bool initializeSDLGameObjects();
void destroySDLGameObjects();

void manageEvents(SDL_Event *event);

void displayGame();
void displayTitleScreen();
void displayEnterPlayer1Name();
void displayEnterPlayer2Name();
void displayEnterPlayerName();
void displayPlayGame();
void displayPlayerScoreboardName(LabelObj *labelObj, const int scoreBoardWidth, const int x, const int y);

//Game phase
bool changeGamePhaseIfNeeded();
void moveToEnterPlayerName(GameMode mode, char *playerName);
void moveToPlayGame();
#endif