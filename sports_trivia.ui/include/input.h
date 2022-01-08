#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

int getChoosenNumberFromKey(SDL_Keycode code, unsigned int minValue, unsigned int maxValue);

#endif