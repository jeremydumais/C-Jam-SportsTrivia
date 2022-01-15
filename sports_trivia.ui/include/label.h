#ifndef LABEL_H
#define LABEL_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//Colors 
SDL_Color lightBlue;
SDL_Color white;
SDL_Color orange;

//Fonts
TTF_Font *titleFont;
TTF_Font *playerNameEditFont;
TTF_Font *scoreFont;
TTF_Font *questionFont;
TTF_Font *answerFont;

typedef struct
{
    SDL_Surface *surface;
    SDL_Texture *texture;
} LabelObj;

typedef struct {
    LabelObj *textObject;
    const char *textValue;
    TTF_Font *font;
    SDL_Color *color;
} InitLabelObj;

LabelObj titleLabelObjBlue;
LabelObj titleLabelObjOrange;
LabelObj titleEnterToStartLabelObj;
LabelObj typePlayer1NameLabelObj;
LabelObj typePlayer2NameLabelObj;
LabelObj typePlayerNameLabelResultObj;
LabelObj typePlayerNameLabelResultCaretObj;
LabelObj scoreBoardPlayer1NameLabelObj;
LabelObj scoreBoardPlayer2NameLabelObj;
LabelObj scoreBoardPlayer1ScoreLabelObj;
LabelObj scoreBoardPlayer2ScoreLabelObj;
LabelObj gameQuestionLabelObj;
LabelObj gameAnswer1LabelObj;
LabelObj gameAnswer2LabelObj;
LabelObj gameAnswer3LabelObj;
LabelObj gameAnswer4LabelObj;
LabelObj endGameMessageLabelObj;
LabelObj endGameKeepSameUsersLabelObj;

bool initializeLabel(SDL_Renderer *renderer, 
                    LabelObj *object, 
                    const char *textValue,
                    TTF_Font *font, 
                    SDL_Color *color);

void displayLabel(SDL_Renderer *renderer, 
                 const LabelObj *object, 
                 int x, 
                 int y);

void destroyLabel(LabelObj *object);

bool setLabelText(SDL_Renderer *renderer, 
                  LabelObj *object, 
                  const char *textValue,
                  TTF_Font *font, 
                  SDL_Color *color);

bool initializeGameLabels(SDL_Renderer *renderer);
void destroyGameLabels();

TTF_Font *initializeFont(const char *filePath, int size);
void destroyFont(TTF_Font *font);

void initializeColors();
bool initializeFonts();
void destroyFonts();

#endif