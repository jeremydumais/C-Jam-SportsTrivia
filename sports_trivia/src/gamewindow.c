#include "gamewindow.h"

SDL_Window *createGameWindow()
{
    return SDL_CreateWindow("Sports Trivia",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 640, 
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED);
}

void destrowGameWindow(SDL_Window *window)
{
    SDL_DestroyWindow(window);
}

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