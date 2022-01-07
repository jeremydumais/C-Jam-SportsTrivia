#include "gamewindow.h"
#include "text.h"

SDL_Window *createGameWindow()
{
    return SDL_CreateWindow("Sports Trivia",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 640, 
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL); //| SDL_WINDOW_MAXIMIZED);
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

void initializeColors()
{
    lightBlue.r = 50;
    lightBlue.g = 50;
    lightBlue.b = 255;
}

bool initializeFonts()
{
    const char *FONTPATH = "bin/resources/hh-agallas-college.ttf";
    titleFont = initializeFont(FONTPATH, 98);
    if (!titleFont) {
        return false;
    }
    return playerNameEditFont = initializeFont(FONTPATH, 60);
}

void destroyFonts()
{
    destroyFont(titleFont);
    destroyFont(playerNameEditFont);
}