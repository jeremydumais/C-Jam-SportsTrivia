#include "texture.h"

SDL_Texture *createTextureFromImageFile(SDL_Renderer *renderer, const char *imagePath)
{
    SDL_Surface *image = SDL_LoadBMP(imagePath);
    if (!image) {
        return NULL;
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return texture;   
}