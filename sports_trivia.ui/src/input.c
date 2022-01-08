#include "input.h"

int getChoosenNumberFromKey(SDL_Keycode code, unsigned int minValue, unsigned int maxValue)
{
    if (code >= SDLK_0 + minValue &&
        code <= SDLK_0 + maxValue) {
        return code - SDLK_0;
    }
    if (code >= SDLK_KP_1 + (minValue - 1) &&
        code <= SDLK_KP_1 + (maxValue - 1)) {
        return (code - SDLK_KP_1) + 1;
    }
    if (code == SDLK_KP_0 && minValue == 0) {
        return 0;
    }
    return -1;
}
