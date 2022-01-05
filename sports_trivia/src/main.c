#include "../include/gamewindow.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    //Display the game board
    bool quit = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window *window = createGameWindow();
    if (!window) 
    {
        printf("Unable to create the SDL Window\n");
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *backgroundTexture = createTextureFromImageFile(renderer, 
                                                                "sports_trivia/resources/image.bmp");

    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderPresent(renderer);

    }
    
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    destrowGameWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}