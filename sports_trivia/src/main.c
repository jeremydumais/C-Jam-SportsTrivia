#include "main.h"
#include "input.h"
#include "text.h"
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
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

    while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (currentGameMode == titleScreen && event.key.keysym.sym == SDLK_RETURN) {
                moveToEnterPlayer1Name();
                break;
            }
            else if (currentGameMode == enterPlayer1Name && event.key.keysym.sym == SDLK_RETURN) {
                if (strlen(currentInput) > 0) {
                    moveToEnterPlayer2Name();
                    break;
                }
                break;
            }
            if(currentInputMode == EditText) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    
                    currentInputMode = NoInput;
                    break;
                }
                size_t inputLength = strlen(currentInput);
                if (event.key.keysym.sym == SDLK_BACKSPACE && 
                    inputLength > 0) {
                    currentInput[inputLength-1] = '\0';
                    currentInputNeedToRerender = true;
               }
            }
            else if (currentInputMode == ChooseNumber) {
                int choiceResult = getChoosenNumberFromKey(event.key.keysym.sym, currentChoiceMin, currentChoiceMax);
                if(choiceResult >= 0) {
                    *currentChoiceResult = (unsigned int)choiceResult;
                }
            }
            break;
        case SDL_TEXTINPUT:
            if(currentInputMode == EditText && !(SDL_GetModState() & KMOD_CTRL && 
                                                    (event.text.text[0] == 'c' || 
                                                     event.text.text[0] == 'C' || 
                                                     event.text.text[0] == 'v' || 
                                                     event.text.text[0] == 'V'))) {
                if (strlen(currentInput) < currentInputMaxLength) {
                    strcat(currentInput, event.text.text);
                }
                currentInputNeedToRerender = true;
            }
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
        SDL_GetWindowSize(window, &windowWidth, NULL);
        windowXCenter = (windowWidth / 2);

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        if (currentGameMode == titleScreen) {
            displayTitleScreen();
        }
        else if (currentGameMode == enterPlayer1Name) {
            displayEnterPlayer1Name();
        }
        else if (currentGameMode == enterPlayer2Name) {
            displayEnterPlayer2Name();
        }
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
    backgroundTexture = createTextureFromImageFile(renderer, 
                                                   "sports_trivia/resources/wallpaper.bmp");
    if (!backgroundTexture) {
        printf("Unable to initialize the background image : %s\n", SDL_GetError());
        return false;
    }
    if (!initializeText(renderer, &titleTextObjBlue, "Sports Trivia", titleFont, &lightBlue)) {
        printf("Unable to initialize the text : %s\n", SDL_GetError());
        return false;
    }
    if (!initializeText(renderer, &titleTextObjWhite, "Sports Trivia", titleFont, &lightGray)) {
        printf("Unable to initialize the text : %s\n", SDL_GetError());
        return false;
    }
    if (!initializeText(renderer, &typePlayer1NameTextObj, "Type player 1 name :", playerNameEditFont, &lightBlue)) {
        printf("Unable to initialize the text : %s\n", SDL_GetError());
        return false;
    }
    if (!initializeText(renderer, &typePlayer2NameTextObj, "Type player 2 name :", playerNameEditFont, &lightBlue)) {
        printf("Unable to initialize the text : %s\n", SDL_GetError());
        return false;
    }
    if (!initializeText(renderer, &typePlayerNameTextResultObj, player1Name, playerNameEditFont, &lightBlue)) {
        printf("Unable to initialize the text : %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void destroySDLGameObjects()
{
    destroyText(&titleTextObjBlue);
    destroyText(&titleTextObjWhite);
    destroyText(&typePlayer1NameTextObj);
    destroyText(&typePlayerNameTextResultObj);
    SDL_DestroyTexture(backgroundTexture);
}

void displayTitleScreen()
{
    displayText(renderer, &titleTextObjBlue, windowXCenter - (titleTextObjBlue.surface->w / 2), 40);
}

void displayEnterPlayer1Name()
{
    displayText(renderer, &titleTextObjWhite, 40, 10);
    displayText(renderer, &typePlayer1NameTextObj, windowXCenter - (typePlayer1NameTextObj.surface->w / 2), 250);
    if (currentInputMode == EditText) {
        if (currentInputNeedToRerender) {
            destroyText(&typePlayerNameTextResultObj);
            initializeText(renderer, currentInputTextObj, currentInput, playerNameEditFont, &lightBlue);
            currentInputNeedToRerender = false;
        }
        if (strlen(currentInput) > 0) {
            displayText(renderer, &typePlayerNameTextResultObj, windowXCenter - (typePlayerNameTextResultObj.surface->w / 2), 320);
        }
    }
}

void displayEnterPlayer2Name()
{
    displayText(renderer, &titleTextObjWhite, 40, 10);
    displayText(renderer, &typePlayer2NameTextObj, windowXCenter - (typePlayer2NameTextObj.surface->w / 2), 250);
    if (currentInputMode == EditText) {
        if (currentInputNeedToRerender) {
            destroyText(&typePlayerNameTextResultObj);
            initializeText(renderer, currentInputTextObj, currentInput, playerNameEditFont, &lightBlue);
            currentInputNeedToRerender = false;
        }
        if (strlen(currentInput) > 0) {
            displayText(renderer, &typePlayerNameTextResultObj, windowXCenter - (typePlayerNameTextResultObj.surface->w / 2), 320);
        }
    }
}

void moveToEnterPlayer1Name()
{
    currentGameMode = enterPlayer1Name;
    currentInputMode = EditText;
    currentInputNeedToRerender = true;
    currentInput = player1Name;
    currentInputMaxLength = PLAYERNAME_MAXLENGTH;
    currentInputTextObj = &typePlayerNameTextResultObj;
}

void moveToEnterPlayer2Name()
{
    currentGameMode = enterPlayer2Name;
    currentInputMode = EditText;
    currentInputNeedToRerender = true;
    currentInput = player2Name;
    currentInputMaxLength = PLAYERNAME_MAXLENGTH;
    currentInputTextObj = &typePlayerNameTextResultObj;
}