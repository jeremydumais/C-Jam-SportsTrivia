#include "main.h"
#include "dataservices.h"
#include "input.h"
#include "label.h"
#include "player.h"
#include "texture.h"
#include "trivia.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    /*DataQueryResult *result = getQueryData("SELECT * FROM Question", extractQuestionList);
    if (!result) {
        printf("%s", getLastDatabaseErrorMsg());
    }
    printf("test %d\n", result->count);
    free(result);

    return EXIT_FAILURE;*/

    if (!initializeSDL()) {
        return EXIT_FAILURE;
    }

    window = createGameWindow();
    if (!window) {
        printf("Unable to create the SDL Window : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!initializeSDLGameObjects()) {
        return EXIT_FAILURE;
    }
    initializeDatabase();
    initializePlayersData();

    while (!quit)
    {
        SDL_WaitEvent(&event);
        manageEvents(&event);
        SDL_GetWindowSize(window, &windowWidth, NULL);
        windowXCenter = (windowWidth / 2);
        displayGame();
        SDL_RenderPresent(renderer);
    }
    destroySDLGameObjects();
    destroySDL();
    return EXIT_SUCCESS;
}

bool initializeSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error intializing SDL: %s\n", SDL_GetError());
		return false;
    }

	if (TTF_Init() < 0) {
		printf("Error intializing SDL_ttf: %s\n", TTF_GetError());
		return false;
	}

    SDL_StartTextInput();
    initializeColors();
    if (!initializeFonts()) {
        printf("Unable to initialize fonts : %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void destroySDL()
{
    SDL_DestroyRenderer(renderer);
    destrowGameWindow(window);
    destroyFonts();
    TTF_Quit();
    SDL_Quit();
}

bool initializeSDLGameObjects()
{
    #define TEXTUREOBJETCSTLENGTH 3
    InitTextureObj textureObjects[TEXTUREOBJETCSTLENGTH] = {{ &backgroundTexture, "sports_trivia/resources/wallpaper.bmp" },
                                                                   { &backgroundTextureTitle, "sports_trivia/resources/wallpaperTitle.bmp" },
                                                                   { &scoreboardTexture, "sports_trivia/resources/scoreboard.bmp" } };
    for(size_t i = 0; i < TEXTUREOBJETCSTLENGTH; i++) {
        (*textureObjects[i].texture) = createTextureFromImageFile(renderer, textureObjects[i].filePath);
        if (!(*textureObjects[i].texture)) {
            printf("Unable to initialize the texture : %s\n", SDL_GetError());
            return false;
        }
    }
    return initializeGameLabels(renderer);
}

void destroySDLGameObjects()
{
    destroyGameLabels();
    SDL_DestroyTexture(scoreboardTexture);
    SDL_DestroyTexture(backgroundTextureTitle);
    SDL_DestroyTexture(backgroundTexture);
}

void manageEvents(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        if (event->key.keysym.sym == SDLK_RETURN && changeGamePhaseIfNeeded()) {
            break;
        }
        if(currentInputMode == EditText) {
            size_t inputLength = strlen(currentInput);
            if (event->key.keysym.sym == SDLK_BACKSPACE && inputLength > 0) {
                currentInput[inputLength-1] = '\0';
                currentInputNeedToRerender = true;
            }
        }
        else if (currentInputMode == ChooseNumber) {
            int choiceResult = getChoosenNumberFromKey(event->key.keysym.sym, currentChoiceMin, currentChoiceMax);
            if(choiceResult >= 0) {
                *currentChoiceResult = (unsigned int)choiceResult;
            }
        }
        break;
    case SDL_TEXTINPUT:
        if(currentInputMode == EditText && !(SDL_GetModState() & KMOD_CTRL && 
                                                (event->text.text[0] == 'c' || 
                                                    event->text.text[0] == 'C' || 
                                                    event->text.text[0] == 'v' || 
                                                    event->text.text[0] == 'V'))) {
            if (strlen(currentInput) < currentInputMaxLength) {
                strcat(currentInput, event->text.text);
            }
            currentInputNeedToRerender = true;
        }
        break;
    case SDL_QUIT:
        quit = true;
        break;
    }
}


void displayGame()
{
    switch(currentGameMode) {
    case titleScreen:
        displayTitleScreen();
        break;
    case enterPlayer1Name:
        displayEnterPlayerName(&typePlayer1NameLabelObj);
        break;
    case enterPlayer2Name:
        displayEnterPlayerName(&typePlayer2NameLabelObj);
        break;
    case playGame:
        displayPlayGame();
        break;
    default:
        break;
    }
}

void displayTitleScreen()
{
    SDL_RenderCopy(renderer, backgroundTextureTitle, NULL, NULL);
    displayLabel(renderer, &titleLabelObjBlue, windowXCenter - (titleLabelObjBlue.surface->w / 2), 40);
}

void displayEnterPlayerName(LabelObj *typePlayerNameTextObj)
{
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    displayLabel(renderer, &titleLabelObjWhite, 40, 10);
    displayLabel(renderer, typePlayerNameTextObj, windowXCenter - (typePlayerNameTextObj->surface->w / 2), 250);
    if (currentInputMode == EditText) {
        if (currentInputNeedToRerender) {
            destroyLabel(&typePlayerNameLabelResultObj);
            initializeLabel(renderer, currentInputTextObj, currentInput, playerNameEditFont, &lightBlue);
            currentInputNeedToRerender = false;
        }
        if (strlen(currentInput) > 0) {
            displayLabel(renderer, &typePlayerNameLabelResultObj, windowXCenter - (typePlayerNameLabelResultObj.surface->w / 2), 320);
        }
    }
}

void displayPlayGame()
{
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    //Scoreboard
    const int SCOREBOARDWIDTH = 400;
    const int SCOREBOARDHEIGHT = 150;
    const int SCOREBOARDPADDING = 10;
    SDL_Rect rectScoreBoardPlayer1Position = { SCOREBOARDPADDING, SCOREBOARDPADDING, SCOREBOARDWIDTH, SCOREBOARDHEIGHT };
    SDL_RenderCopy(renderer, scoreboardTexture, NULL, &rectScoreBoardPlayer1Position);
    SDL_Rect rectScoreBoardPlayer2Position = { windowWidth - (SCOREBOARDWIDTH + SCOREBOARDPADDING), SCOREBOARDPADDING, SCOREBOARDWIDTH, SCOREBOARDHEIGHT };
    SDL_RenderCopy(renderer, scoreboardTexture, NULL, &rectScoreBoardPlayer2Position);
    const int SCOREBOARD1CENTER = SCOREBOARDPADDING + (SCOREBOARDWIDTH / 2);
    const int SCOREBOARD2CENTER = (windowWidth - SCOREBOARDPADDING) - (SCOREBOARDWIDTH / 2);
    //Player names
    displayPlayerScoreboardName(&scoreBoardPlayer1NameLabelObj, SCOREBOARDWIDTH,
                                SCOREBOARD1CENTER - (scoreBoardPlayer1NameLabelObj.surface->w/2),
                                SCOREBOARDPADDING);
    displayPlayerScoreboardName(&scoreBoardPlayer2NameLabelObj, SCOREBOARDWIDTH,
                                SCOREBOARD2CENTER - (scoreBoardPlayer2NameLabelObj.surface->w/2),
                                SCOREBOARDPADDING);                            
    //Scores
    displayLabel(renderer, &scoreBoardPlayer1ScoreLabelObj, SCOREBOARD1CENTER - (scoreBoardPlayer1ScoreLabelObj.surface->w/2), 80);
    displayLabel(renderer, &scoreBoardPlayer2ScoreLabelObj, SCOREBOARD2CENTER - (scoreBoardPlayer2ScoreLabelObj.surface->w/2), 80);
}

void displayPlayerScoreboardName(LabelObj *labelObj, const int scoreBoardWidth, const int x, const int y)
{
    size_t player1NameSurfaceWidth = labelObj->surface->w;
    if (player1NameSurfaceWidth > scoreBoardWidth) {
        //Fit the name in the score board if required
        labelObj->surface->w = scoreBoardWidth - 20;
    }
    displayLabel(renderer, labelObj, x, y);
}

bool changeGamePhaseIfNeeded()
{
    if (currentGameMode == titleScreen) {
        moveToEnterPlayerName(enterPlayer1Name, player1Name);
        return true;
    }
    if (currentGameMode == enterPlayer1Name) {
        if (strlen(currentInput) > 0) {
            destroyLabel(&scoreBoardPlayer1NameLabelObj);
            if (!initializeLabel(renderer, &scoreBoardPlayer1NameLabelObj, player1Name, playerNameEditFont, &white)) {
                printf("Unable to initialize the text : %s\n", SDL_GetError());
            }
            moveToEnterPlayerName(enterPlayer2Name, player2Name);
            return true;
        }
    }
    if (currentGameMode == enterPlayer2Name) {
        if (strlen(currentInput) > 0) {
            destroyLabel(&scoreBoardPlayer2NameLabelObj);
            if (!initializeLabel(renderer, &scoreBoardPlayer2NameLabelObj, player2Name, playerNameEditFont, &white)) {
                printf("Unable to initialize the text : %s\n", SDL_GetError());
            }
            moveToPlayGame();
            return true;
        }
    }
    return false;
}

void moveToEnterPlayerName(GameMode mode, char *playerName)
{
    currentGameMode = mode;
    currentInputMode = EditText;
    currentInputNeedToRerender = true;
    currentInput = playerName;
    currentInputMaxLength = PLAYERNAME_MAXLENGTH;
    currentInputTextObj = &typePlayerNameLabelResultObj;
}

void moveToPlayGame()
{
    currentGameMode = playGame;
    currentInputMode = EditText;
}