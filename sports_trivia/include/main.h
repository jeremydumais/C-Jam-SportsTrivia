#ifndef MAIN_H
#define MAIN_H

#include "gamewindow.h"
#include "player.h"

enum gameMode { titleScreen, 
                enterPlayer1Name, 
                enterPlayer2Name, 
                playGame, 
                endGame };

enum gameMode currentGameMode = titleScreen;
enum inputMode currentInputMode = NoInput;
char player1Name[PLAYERNAME_MAXLENGTH+1] = "Player1";
char player2Name[PLAYERNAME_MAXLENGTH+1] = "Player2";

//Text input objets
char *currentInput = NULL;
int currentInputMaxLength = 0;
struct TextObj *currentInputTextObj = NULL;
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
SDL_Texture *backgroundTexture = NULL;
struct TextObj titleTextObjBlue;
struct TextObj titleTextObjWhite;
struct TextObj typePlayer1NameTextObj;
struct TextObj typePlayer2NameTextObj;
struct TextObj typePlayerNameTextResultObj;


bool initializeSDL();
void destroySDL();

bool initializeSDLGameObjects();
void destroySDLGameObjects();

void displayTitleScreen();
void displayEnterPlayer1Name();
void displayEnterPlayer2Name();

//Game phase
void moveToEnterPlayer1Name();
void moveToEnterPlayer2Name();
#endif