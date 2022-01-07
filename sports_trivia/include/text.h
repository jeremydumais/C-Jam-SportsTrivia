#ifndef TEXT_H
#define TEXT_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct TextObj
{
    SDL_Surface *surface;
    SDL_Texture *texture;
};

bool initializeText(SDL_Renderer *renderer, 
                    struct TextObj *object, 
                    const char *textValue,
                    TTF_Font *font, 
                    SDL_Color *color);

void displayText(SDL_Renderer *renderer, 
                 const struct TextObj *object, 
                 int x, 
                 int y);

void destroyText(struct TextObj *object);

TTF_Font *initializeFont(const char *filePath, int size);
void destroyFont(TTF_Font *font);

#endif