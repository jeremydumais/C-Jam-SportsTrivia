#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

SDL_Texture *createTextureFromImageFile(SDL_Renderer *renderer, const char *imagePath);

#endif