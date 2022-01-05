#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL2/SDL.h>

SDL_Window *createGameWindow();
void destrowGameWindow();
SDL_Texture *createTextureFromImageFile(SDL_Renderer *renderer, const char *imagePath);
#endif