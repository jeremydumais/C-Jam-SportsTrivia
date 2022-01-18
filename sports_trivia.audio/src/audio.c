#include "audio.h"

bool initializeMusic()
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

    backgroundMusic = Mix_LoadMUS("sports_trivia/resources/music.wav");
    if (!backgroundMusic) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }
    Mix_VolumeMusic(5);
    
    keyPressSound = Mix_LoadWAV("sports_trivia/resources/keypress.wav");
    if (!keyPressSound) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }
    Mix_VolumeChunk(keyPressSound, 30);

    backspaceSound = Mix_LoadWAV("sports_trivia/resources/backspace.wav");
    if (!backspaceSound) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }
    Mix_VolumeChunk(backspaceSound, 30);

    errorSound = Mix_LoadWAV("sports_trivia/resources/error.ogg");
    if (!errorSound) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }

    goodAnswerSound = Mix_LoadWAV("sports_trivia/resources/goodanswer.wav");
    if (!goodAnswerSound) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }
    return true;
}