#include "gamewindow.h"
#include "player.h"
#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
    enum inputMode currentInputMode = EditText;
    char player1Name[PLAYERNAME_MAXLENGTH+1] = "Player1";
    char player2Name[PLAYERNAME_MAXLENGTH+1] = "Player2";

    char *currentInput = NULL;
    int currentInputMaxLength = 0;
    struct TextObj *currentInputTextObj = NULL;

    bool quit = false;
    SDL_Event event;
    struct TextObj titleTextObj;
    struct TextObj typePlayerNameTextObj;
    struct TextObj typePlayerNameTextResultObj;

    currentInput = player1Name;
    currentInputMaxLength = PLAYERNAME_MAXLENGTH;
    currentInputTextObj = &typePlayerNameTextResultObj;
    bool currentInputNeedToRerender = true;


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error intializing SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

	if (TTF_Init() < 0) {
		printf("Error intializing SDL_ttf: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}

    SDL_StartTextInput();
    initializeColors();
    if (!initializeFonts()) {
        printf("Unable to initialize fonts : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = createGameWindow();
    if (!window) {
        printf("Unable to create the SDL Window\n");
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *backgroundTexture = createTextureFromImageFile(renderer, 
                                                                "bin/resources/image.bmp");

    if (!initializeText(renderer, &titleTextObj, "Sports Trivia", titleFont, &lightBlue)) {
        printf("Unable to initialize the text : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    if (!initializeText(renderer, &typePlayerNameTextObj, "Type player name :", playerNameEditFont, &lightBlue)) {
        printf("Unable to initialize the text : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    if (!initializeText(renderer, &typePlayerNameTextResultObj, player1Name, playerNameEditFont, &lightBlue)) {
        printf("Unable to initialize the text : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_KEYDOWN:
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

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        int windowWidth;
        SDL_GetWindowSize(window, &windowWidth, NULL);
        int windowXCenter = (windowWidth / 2);
        displayText(renderer, &titleTextObj, windowXCenter - (titleTextObj.surface->w / 2), 80);
        displayText(renderer, &typePlayerNameTextObj, windowXCenter - (typePlayerNameTextObj.surface->w / 2), 250);
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
        SDL_RenderPresent(renderer);
    }

    destroyText(&titleTextObj);
    destroyText(&typePlayerNameTextObj);
    destroyText(&typePlayerNameTextResultObj);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    destrowGameWindow(window);
    destroyFonts();
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}