#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

enum inputMode { NoInput, EditText };

//Colors 
SDL_Color lightBlue;

//Fonts
TTF_Font *titleFont;
TTF_Font *playerNameEditFont;

SDL_Window *createGameWindow();
void destrowGameWindow();
SDL_Texture *createTextureFromImageFile(SDL_Renderer *renderer, const char *imagePath);
void initializeColors();
bool initializeFonts();
void destroyFonts();

#endif