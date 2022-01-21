#include "audio.h"
#include <limits.h>
#include <string.h>

bool initializeMusic(const char *executablePath)
{
    char musicPath[PATH_MAX+FILENAME_MAX];
    char keyPressPath[PATH_MAX+FILENAME_MAX];
    char backspacePath[PATH_MAX+FILENAME_MAX];
    char errorPath[PATH_MAX+FILENAME_MAX];
    char goodAnswerPath[PATH_MAX+FILENAME_MAX];
    sprintf(musicPath, "%s/%s", executablePath, "resources/music.wav");
    sprintf(keyPressPath, "%s/%s", executablePath, "resources/keypress.wav");
    sprintf(backspacePath, "%s/%s", executablePath, "resources/backspace.wav");
    sprintf(errorPath, "%s/%s", executablePath, "resources/error.ogg");
    sprintf(goodAnswerPath, "%s/%s", executablePath, "resources/goodanswer.wav");
    
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

    backgroundMusic = Mix_LoadMUS(musicPath);
    if (!backgroundMusic) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }
    Mix_VolumeMusic(5);
    
    keyPressSound = Mix_LoadWAV(keyPressPath);
    if (!keyPressSound) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }
    Mix_VolumeChunk(keyPressSound, 30);

    backspaceSound = Mix_LoadWAV(backspacePath);
    if (!backspaceSound) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }
    Mix_VolumeChunk(backspaceSound, 30);

    errorSound = Mix_LoadWAV(errorPath);
    if (!errorSound) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }

    goodAnswerSound = Mix_LoadWAV(goodAnswerPath);
    if (!goodAnswerSound) {
        fprintf(stderr, "Unable to load the sound. %s\n", Mix_GetError());
        return false;
    }
    return true;
}