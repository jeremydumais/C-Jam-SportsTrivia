#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

Mix_Music *backgroundMusic;
Mix_Chunk *keyPressSound;
Mix_Chunk *backspaceSound;
Mix_Chunk *errorSound;
Mix_Chunk *goodAnswerSound;

bool initializeMusic();

#endif