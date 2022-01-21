#ifndef MAIN_H
#define MAIN_H

#include "gamewindow.h"
#include "label.h"
#include "player.h"
#include "trivia.h"
#include "vector.h"

typedef enum { titleScreen, 
              enterPlayer1Name, 
              enterPlayer2Name, 
              playGame, 
              endGame } GameMode;

GameMode currentGameMode = titleScreen;
InputMode currentInputMode = NoInput;

char *executablePath = NULL;

//Text input objets
char *currentInput = NULL;
int currentInputMaxLength = 0;
LabelObj *currentInputTextObj = NULL;
bool currentInputNeedToRerender = true;

//Number choice objects
unsigned int currentChoiceMin = 0;
unsigned int currentChoiceMax = 0;
unsigned int *currentChoiceResult = NULL;

//Boolean choice
bool boolChoiceResult = false;

bool quit = false;

//Graphical objects
SDL_Event event;
SDL_Window *window = NULL;
int windowWidth = 0;
int windowHeight = 0;
int windowXCenter = 0;
int windowYCenter = 0;
Uint32 delta;
double glowState = 200.0;
bool glowDecrease = true;
SDL_Renderer *renderer = NULL;

typedef struct {
    SDL_Texture **texture;
    const char *filePath;
} InitTextureObj;
SDL_Texture *backgroundTexture = NULL;
SDL_Texture *backgroundTextureTitle = NULL;
SDL_Texture *scoreboardTexture = NULL;

//Trivia objects
vector *currentGameQuestions = NULL;
vector *currentQuestionAnswers = NULL;
int currentQuestionIndex;
unsigned int currentPlayerTurnIndex;
int choosenAnswer;

bool initializeSDL(const char *executablePath);
void destroySDL();

bool initializeSDLGameObjects(const char *executablePath);
void destroySDLGameObjects();

void freeQuestions();
void freeAnswers();

void manageEvents();

void displayGame();
void glowLabelObj(LabelObj *labelObj);
void displayTitleScreen();
void displayEnterPlayer1Name();
void displayEnterPlayer2Name();
void displayEnterPlayerName();
void displayPlayGame();
void displayScoreBoardObjects();
void displayLabelWidthMaxCheck(LabelObj *labelObj, const int scoreBoardWidth, const int x, const int y);
void displayCenteredScreenLabel(LabelObj *labelObj, const int y);
void displayEndGame();

//Game phase
bool changeGamePhaseIfNeeded();
void moveToEnterPlayerName(GameMode mode, char *playerName);
void moveToInitializeGame();
void moveToGame();
bool loadQuestionWithAnswers(Question *question);
void playerSubmitAnswer();
bool incrementScoreForCurrentPlayer();
void changePlayerTurn();
bool changeToNextQuestion();
void moveToEnd();
#endif