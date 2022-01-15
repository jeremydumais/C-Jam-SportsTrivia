#include "gamewindow.h"
#include "label.h"

SDL_Window *createGameWindow()
{
    SDL_Window *window = SDL_CreateWindow("Sports Trivia",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 640, 
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED);
    SDL_SetWindowMinimumSize(window, 960, 640);
    return window;
}

void destrowGameWindow(SDL_Window *window)
{
    SDL_DestroyWindow(window);
}