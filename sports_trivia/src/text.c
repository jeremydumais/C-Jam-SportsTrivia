#include "text.h"

bool initializeText(SDL_Renderer *renderer, 
                    struct TextObj *object, 
                    const char *textValue,
                    TTF_Font *font, 
                    SDL_Color *color)
{
    object->surface = TTF_RenderText_Solid(font, textValue, *color); 
    if (!object->surface) {
        return false;
    }
    object->texture = SDL_CreateTextureFromSurface(renderer, object->surface);
    return object->texture != NULL;
}

void displayText(SDL_Renderer *renderer, 
                 const struct TextObj *object, 
                 int x, 
                 int y)
{
    SDL_Rect messageRect;
    messageRect.x = x;
    messageRect.y = y;
    messageRect.w = object->surface->w;
    messageRect.h = object->surface->h;
    SDL_RenderCopy(renderer, object->texture, NULL, &messageRect);
}

void destroyText(struct TextObj *object)
{
    SDL_FreeSurface(object->surface);
    SDL_DestroyTexture(object->texture);  
    object->surface = NULL;
    object->texture = NULL;
}

TTF_Font *initializeFont(const char *filePath, int size)
{
    return TTF_OpenFont(filePath, size);
}

void destroyFont(TTF_Font *font)
{
    TTF_CloseFont(font);
    font = NULL;
}
