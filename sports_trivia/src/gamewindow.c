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

void initializeColors()
{
    lightBlue.r = 50;
    lightBlue.g = 50;
    lightBlue.b = 255;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    lightGray.r = 255;
    lightGray.g = 80;
    lightGray.b = 40;
}

bool initializeFonts()
{
    const char *FONTPATH = "sports_trivia/resources/hh-agallas-college.ttf";
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

int getChoosenNumberFromKey(SDL_Keycode code, int minValue, int maxValue)
{
    return -1;
}