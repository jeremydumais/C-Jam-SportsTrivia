#include "label.h"

bool initializeLabel(SDL_Renderer *renderer, 
                    LabelObj *object, 
                    const char *textValue,
                    TTF_Font *font, 
                    SDL_Color *color)
{
    object->surface = TTF_RenderText_Solid(font, 
                                           strlen(textValue) == 0 ? " " : textValue, 
                                           *color); 
    if (!object->surface) {
        return false;
    }
    object->texture = SDL_CreateTextureFromSurface(renderer, object->surface);
    return object->texture != NULL;
}

void displayLabel(SDL_Renderer *renderer, 
                 const LabelObj *object, 
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

void destroyLabel(LabelObj *object)
{
    SDL_FreeSurface(object->surface);
    SDL_DestroyTexture(object->texture);  
    object->surface = NULL;
    object->texture = NULL;
}

bool initializeGameLabels(SDL_Renderer *renderer)
{
    #define TEXTOBJETCSTLENGTH 7
    InitLabelObj textObjects[TEXTOBJETCSTLENGTH] = {{ &titleLabelObjBlue, "Sports Trivia", titleFont, &lightBlue },
                                                          { &titleLabelObjWhite, "Sports Trivia", titleFont, &orange },
                                                          { &typePlayer1NameLabelObj, "Type player 1 name :", playerNameEditFont, &lightBlue },
                                                          { &typePlayer2NameLabelObj, "Type player 2 name :", playerNameEditFont, &lightBlue },
                                                          { &typePlayerNameLabelResultObj, "", playerNameEditFont, &lightBlue },
                                                          { &scoreBoardPlayer1ScoreLabelObj, "0", scoreFont, &orange },
                                                          { &scoreBoardPlayer2ScoreLabelObj, "0", scoreFont, &orange } };
    bool error = false;
    for(size_t i = 0; i < TEXTOBJETCSTLENGTH; i++) {
        if (!initializeLabel(renderer, textObjects[i].textObject, textObjects[i].textValue, textObjects[i].font, textObjects[i].color)) {
            printf("Unable to initialize the text : %s\n", SDL_GetError());
            error = true;
            break;
        }
    }
    return !error;
}

void destroyGameLabels()
{
    destroyLabel(&titleLabelObjBlue);
    destroyLabel(&titleLabelObjWhite);
    destroyLabel(&typePlayer1NameLabelObj);
    destroyLabel(&typePlayer2NameLabelObj);
    destroyLabel(&typePlayerNameLabelResultObj);
    destroyLabel(&scoreBoardPlayer1NameLabelObj);
    destroyLabel(&scoreBoardPlayer2NameLabelObj);
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

void initializeColors()
{
    lightBlue.r = 50;
    lightBlue.g = 50;
    lightBlue.b = 255;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    orange.r = 255;
    orange.g = 80;
    orange.b = 40;
}

bool initializeFonts()
{
    const char *MAINFONTPATH = "sports_trivia/resources/hh-agallas-college.ttf";
    titleFont = initializeFont(MAINFONTPATH, 98);
    if (!titleFont) {
        return false;
    }
    playerNameEditFont = initializeFont(MAINFONTPATH, 60);
    if (!playerNameEditFont) {
        return false;
    }
    scoreFont = initializeFont("sports_trivia/resources/scoreboard.ttf", 60);
    return scoreFont != NULL;
}

void destroyFonts()
{
    destroyFont(titleFont);
    destroyFont(playerNameEditFont);
    destroyFont(scoreFont);
}