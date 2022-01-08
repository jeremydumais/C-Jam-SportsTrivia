#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

enum inputMode { NoInput, EditText, ChooseNumber };

//Colors 
SDL_Color lightBlue;
SDL_Color white;
SDL_Color lightGray;

//Fonts
TTF_Font *titleFont;
TTF_Font *playerNameEditFont;

SDL_Window *createGameWindow();
void destrowGameWindow();
void initializeColors();
bool initializeFonts();
void destroyFonts();

#endif