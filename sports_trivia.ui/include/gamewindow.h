#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef enum { NoInput, EditText, ChooseNumber } InputMode;

SDL_Window *createGameWindow();
void destrowGameWindow();

#endif