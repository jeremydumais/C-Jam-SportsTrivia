#include "main.h"
#include "audio.h"
#include "dataservices.h"
#include "input.h"
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    if (!initializeSDL()) {
        return EXIT_FAILURE;
    }

    window = createGameWindow();
    if (!window) {
        fprintf(stderr, "Unable to create the SDL Window : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!initializeSDLGameObjects()) {
        return EXIT_FAILURE;
    }

    
    if (!initializeMusic()) {
        return EXIT_FAILURE;
    }
    initializeDatabase();
    initializePlayersData();
    
    Mix_PlayMusic(backgroundMusic, -1);
    Uint32 oldTime = SDL_GetTicks();
    Uint32 newTime;
    while (!quit)
    {
        newTime = SDL_GetTicks();
        delta = newTime - oldTime;
        manageEvents();
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        windowXCenter = (windowWidth / 2);
        windowYCenter = (windowHeight / 2);
        displayGame();
        SDL_RenderPresent(renderer);
        SDL_RenderFlush(renderer);
        if (delta >= 1) {
            oldTime = newTime;
        }
    }
    freeAnswers();
    freeQuestions();
    destroySDLGameObjects();
    destroySDL();
    return EXIT_SUCCESS;
}

bool initializeSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Error intializing SDL: %s\n", SDL_GetError());
		return false;
    }

	if (TTF_Init() < 0) {
		fprintf(stderr, "Error intializing SDL_ttf: %s\n", TTF_GetError());
		return false;
	}

    SDL_StartTextInput();
    initializeColors();
    if (!initializeFonts()) {
        fprintf(stderr, "Unable to initialize fonts : %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void destroySDL()
{
    SDL_DestroyRenderer(renderer);
    destrowGameWindow(window);
    destroyFonts();
    TTF_Quit();
    SDL_Quit();
}

bool initializeSDLGameObjects()
{
    #define TEXTUREOBJETCSTLENGTH 3
    InitTextureObj textureObjects[TEXTUREOBJETCSTLENGTH] = {{ &backgroundTexture, "sports_trivia/resources/wallpaper.bmp" },
                                                                   { &backgroundTextureTitle, "sports_trivia/resources/wallpaperTitle.bmp" },
                                                                   { &scoreboardTexture, "sports_trivia/resources/scoreboard.bmp" } };
    for(size_t i = 0; i < TEXTUREOBJETCSTLENGTH; i++) {
        (*textureObjects[i].texture) = createTextureFromImageFile(renderer, textureObjects[i].filePath);
        if (!(*textureObjects[i].texture)) {
            fprintf(stderr, "Unable to initialize the texture : %s\n", SDL_GetError());
            return false;
        }
    }
    return initializeGameLabels(renderer);
}

void destroySDLGameObjects()
{
    destroyGameLabels();
    SDL_DestroyTexture(scoreboardTexture);
    SDL_DestroyTexture(backgroundTextureTitle);
    SDL_DestroyTexture(backgroundTexture);
}

void freeQuestions()
{  
    vectorFree(currentGameQuestions);
    free(currentGameQuestions);
    currentGameQuestions = NULL;
}

void freeAnswers()
{
    vectorFree(currentQuestionAnswers);
    free(currentQuestionAnswers);
    currentQuestionAnswers = NULL;
}
void manageEvents()
{
    while(SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RETURN && changeGamePhaseIfNeeded()) {
                break;
            }
            if(currentInputMode == EditText) {
                size_t inputLength = strlen(currentInput);
                if (event.key.keysym.sym == SDLK_BACKSPACE && inputLength > 0) {
                    currentInput[inputLength-1] = '\0';
                    currentInputNeedToRerender = true;
                    Mix_PlayChannel(-1, backspaceSound, 0);
                }
            }
            else if (currentInputMode == ChooseNumber) {
                int choiceResult = getChoosenNumberFromKey(event.key.keysym.sym, currentChoiceMin, currentChoiceMax);
                if(choiceResult >= 0) {
                    *currentChoiceResult = (unsigned int)choiceResult;
                    if (currentGameMode == playGame) {
                        playerSubmitAnswer();
                    }
                }
            }
            else if (currentInputMode == ChooseBool) {
                if (event.key.keysym.sym == SDLK_y) {
                    boolChoiceResult = true;
                    playerSubmitAnswer();
                }
                if (event.key.keysym.sym == SDLK_n) {
                    boolChoiceResult = false;
                    playerSubmitAnswer();
                }
                SDL_FlushEvent(SDL_TEXTINPUT);
            }
            break;
        case SDL_TEXTINPUT:
            if(currentInputMode == EditText && !(SDL_GetModState() & KMOD_CTRL && 
                                                    (event.text.text[0] == 'c' || 
                                                        event.text.text[0] == 'C' || 
                                                        event.text.text[0] == 'v' || 
                                                        event.text.text[0] == 'V'))) {
                if (strlen(currentInput) < currentInputMaxLength) {
                    strcat(currentInput, event.text.text);
                    Mix_PlayChannel(-1, keyPressSound, 0);
                }
                currentInputNeedToRerender = true;
            }
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
}


void displayGame()
{
    switch(currentGameMode) {
    case titleScreen:
        displayTitleScreen();
        break;
    case enterPlayer1Name:
        displayEnterPlayerName(&typePlayer1NameLabelObj);
        break;
    case enterPlayer2Name:
        displayEnterPlayerName(&typePlayer2NameLabelObj);
        break;
    case playGame:
        displayPlayGame();
        break;
    case endGame:
        displayEndGame();
        break;
    default:
        break;
    }
}

void glowLabelObj(LabelObj *labelObj)
{
    if (delta >= 1) {
        if (glowDecrease) {
            glowState-= delta/6.0;
        }
        else {
            glowState+= delta/6.0;
        }
        if (glowState < 40) {
            glowDecrease = false;
            glowState = 40;
        }
        else if (glowState >= 255) {
            glowDecrease = true;
            glowState = 255;
        }
        SDL_SetTextureAlphaMod(labelObj->texture, glowState);
    }    
}

void displayTitleScreen()
{
    SDL_RenderCopy(renderer, backgroundTextureTitle, NULL, NULL);
    displayCenteredScreenLabel(&titleLabelObjBlue, 40);
    glowLabelObj(&titleEnterToStartLabelObj);
    displayCenteredScreenLabel(&titleEnterToStartLabelObj, windowYCenter - (titleEnterToStartLabelObj.surface->h/2));
}

void displayEnterPlayerName(LabelObj *typePlayerNameTextObj)
{
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    displayLabel(renderer, &titleLabelObjOrange, 40, 10);
    displayCenteredScreenLabel(typePlayerNameTextObj, 250);
    if (currentInputMode == EditText) {
        if (currentInputNeedToRerender) {
            if (!setLabelText(renderer, currentInputTextObj, currentInput, playerNameEditFont, &white)) {
                quit = true;
                return;
            }
            currentInputNeedToRerender = false;
        }
        if (strlen(currentInput) > 0) {
            displayCenteredScreenLabel(&typePlayerNameLabelResultObj, 320);
        }
        glowLabelObj(&typePlayerNameLabelResultCaretObj);
        displayLabel(renderer, &typePlayerNameLabelResultCaretObj, windowXCenter + (typePlayerNameLabelResultObj.surface->w/2), 320);
    }
}

void displayPlayGame()
{
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    displayScoreBoardObjects();
    //Display the question
    displayCenteredScreenLabel(&gameQuestionForLabelObj, 220);
    displayCenteredScreenLabel(&gameQuestionLabelObj, 280);
    displayCenteredScreenLabel(&gameAnswer1LabelObj, 360);
    displayCenteredScreenLabel(&gameAnswer2LabelObj, 420);
    displayCenteredScreenLabel(&gameAnswer3LabelObj, 480);
    displayCenteredScreenLabel(&gameAnswer4LabelObj, 540);
}

void displayScoreBoardObjects()
{
    //Scoreboard
    const int SCOREBOARDWIDTH = 400;
    const int SCOREBOARDHEIGHT = 150;
    const int SCOREBOARDPADDING = 10;
    SDL_Rect rectScoreBoardPlayer1Position = { SCOREBOARDPADDING, SCOREBOARDPADDING, SCOREBOARDWIDTH, SCOREBOARDHEIGHT };
    SDL_RenderCopy(renderer, scoreboardTexture, NULL, &rectScoreBoardPlayer1Position);
    SDL_Rect rectScoreBoardPlayer2Position = { windowWidth - (SCOREBOARDWIDTH + SCOREBOARDPADDING), SCOREBOARDPADDING, SCOREBOARDWIDTH, SCOREBOARDHEIGHT };
    SDL_RenderCopy(renderer, scoreboardTexture, NULL, &rectScoreBoardPlayer2Position);
    const int SCOREBOARD1CENTER = SCOREBOARDPADDING + (SCOREBOARDWIDTH / 2);
    const int SCOREBOARD2CENTER = (windowWidth - SCOREBOARDPADDING) - (SCOREBOARDWIDTH / 2);
    //Player names
    if (currentGameMode == playGame && currentPlayerTurnIndex == 1) {
        glowLabelObj(&scoreBoardPlayer1NameLabelObj);
    } 
    else {
        SDL_SetTextureAlphaMod(scoreBoardPlayer1NameLabelObj.texture, 255);
    }
    displayLabelWidthMaxCheck(&scoreBoardPlayer1NameLabelObj, SCOREBOARDWIDTH,
                                SCOREBOARD1CENTER - (scoreBoardPlayer1NameLabelObj.surface->w/2),
                                SCOREBOARDPADDING);
    if (currentGameMode == playGame && currentPlayerTurnIndex == 2) {
        glowLabelObj(&scoreBoardPlayer2NameLabelObj);
    }
    else {
        SDL_SetTextureAlphaMod(scoreBoardPlayer2NameLabelObj.texture, 255);
    }
    displayLabelWidthMaxCheck(&scoreBoardPlayer2NameLabelObj, SCOREBOARDWIDTH,
                                SCOREBOARD2CENTER - (scoreBoardPlayer2NameLabelObj.surface->w/2),
                                SCOREBOARDPADDING);                            
    //Scores
    displayLabel(renderer, &scoreBoardPlayer1ScoreLabelObj, SCOREBOARD1CENTER - (scoreBoardPlayer1ScoreLabelObj.surface->w/2), 80);
    displayLabel(renderer, &scoreBoardPlayer2ScoreLabelObj, SCOREBOARD2CENTER - (scoreBoardPlayer2ScoreLabelObj.surface->w/2), 80);
}

void displayLabelWidthMaxCheck(LabelObj *labelObj, const int maxWidth, const int x, const int y)
{
    size_t labelSurfaceWidth = labelObj->surface->w;
    if (labelSurfaceWidth > maxWidth) {
        //Fit the name in the score board if required
        labelObj->surface->w = maxWidth - 20;
    }
    displayLabel(renderer, labelObj, x, y);
}

void displayCenteredScreenLabel(LabelObj *labelObj, const int y)
{
    displayLabelWidthMaxCheck(labelObj, windowWidth, windowXCenter - (labelObj->surface->w/2), y);
}

void displayEndGame()
{
    SDL_RenderCopy(renderer, backgroundTextureTitle, NULL, NULL);
    displayScoreBoardObjects();
    displayCenteredScreenLabel(&endGameMessageLabelObj, 300);
    displayCenteredScreenLabel(&endGameKeepSameUsersLabelObj, 380);
}

bool changeGamePhaseIfNeeded()
{
    if (currentGameMode == titleScreen) {
        moveToEnterPlayerName(enterPlayer1Name, player1Name);
        return true;
    }
    if (currentGameMode == enterPlayer1Name) {
        if (strlen(currentInput) > 0) {
            if (!setLabelText(renderer, &scoreBoardPlayer1NameLabelObj, player1Name, playerNameEditFont, &white)) {
                quit = true;
                return false;
            }
            moveToEnterPlayerName(enterPlayer2Name, player2Name);
            return true;
        }
    }
    if (currentGameMode == enterPlayer2Name) {
        if (strlen(currentInput) > 0) {
            if (!setLabelText(renderer, &scoreBoardPlayer2NameLabelObj, player2Name, playerNameEditFont, &white)) {
                quit = true;
                return false;
            }
            moveToInitializeGame();
            return true;
        }
    }
    return false;
}

void moveToEnterPlayerName(GameMode mode, char *playerName)
{
    currentGameMode = mode;
    currentInputMode = EditText;
    currentInputNeedToRerender = true;
    currentInput = playerName;
    currentInputMaxLength = PLAYERNAME_MAXLENGTH;
    currentInputTextObj = &typePlayerNameLabelResultObj;
}

void moveToInitializeGame()
{
    player1Score = 0;
    player2Score = 0;
    if (!setLabelText(renderer, &scoreBoardPlayer1ScoreLabelObj, "0", scoreFont, &orange)) {
        quit = true;
        return;
    }
    if (!setLabelText(renderer, &scoreBoardPlayer2ScoreLabelObj, "0", scoreFont, &orange)) {
        quit = true;
        return;
    }
    currentGameMode = playGame;
    currentInputMode = EditText;
    currentGameQuestions = loadRandomQuestionsFromDatabase(10);
    if (!currentGameQuestions) {
        fprintf(stderr, "Unable to load game questions.\n");
        quit = true;
        return;
    }
    currentQuestionIndex = 0;
    currentPlayerTurnIndex = 1;
    moveToGame();
}

void moveToGame()
{
    //Load the question
    Question *question = vectorGetItem(currentGameQuestions, currentQuestionIndex);
    if (!loadQuestionWithAnswers(question)) {
        return;
    }
    currentInputMode = ChooseNumber;
    currentChoiceMin = 1;
    currentChoiceMax = 4;
    currentChoiceResult = &choosenAnswer;
}

bool loadQuestionWithAnswers(Question *question)
{
    char questionFor[100];
    sprintf(questionFor, "Question for %s", currentPlayerTurnIndex == 1 ? player1Name : player2Name);
    if (!setLabelText(renderer, &gameQuestionForLabelObj, questionFor, answerFont, &lightBlue)) {
        quit = true;
        return false;
    }
    if (!setLabelText(renderer, &gameQuestionLabelObj, question->description, questionFont, &white)) {
        quit = true;
        return false;
    }
    //Load answers for the question
    freeAnswers();
    currentQuestionAnswers = loadAnswersFromQuestionId(question->id);
    if (!currentQuestionAnswers) {
        fprintf(stderr, "Unable to load question answers.\n");
        quit = true;
        return false;
    }
    LabelObj *answersLabelObj[4] = { &gameAnswer1LabelObj, &gameAnswer2LabelObj, &gameAnswer3LabelObj, &gameAnswer4LabelObj };
    for(int i=0; i<vectorGetSize(currentQuestionAnswers); i++) {
        Answer *answer = vectorGetItem(currentQuestionAnswers, i);
        char answerWithChoiceNo[DESCRIPTION_MAX + 3];
        sprintf(answerWithChoiceNo, "%d) %s", i+1, answer->description);
        if (!setLabelText(renderer, answersLabelObj[i], answerWithChoiceNo, answerFont, &white)) {
            quit = true;
            return false;
        }
    }
    return true;
}

void playerSubmitAnswer()
{
    if (currentGameMode == playGame) {
        Question *question = vectorGetItem(currentGameQuestions, currentQuestionIndex);
        //Check if the submitted answers is the good one
        if (choosenAnswer == question->rightAnswerNo) {
            if (!incrementScoreForCurrentPlayer()) {
                return;
            }
            Mix_PlayChannel(-1, goodAnswerSound, 0);
        }
        else {
            Mix_PlayChannel(-1, errorSound, 0);
        } 
        changePlayerTurn();
        if (!changeToNextQuestion()) {
            return;
        }
    }
    else if (currentGameMode == endGame) {
        if (boolChoiceResult) {
            moveToInitializeGame();
        } 
        else {
            strcpy(player1Name, "");
            strcpy(player2Name, "");
            moveToEnterPlayerName(enterPlayer1Name, player1Name);
        }
    }
}

bool incrementScoreForCurrentPlayer()
{
    bool retVal = true;
    int *playerScore;
    LabelObj *playerScoreLabelObj;
    if (currentPlayerTurnIndex == 1) {
        playerScore = &player1Score;
        playerScoreLabelObj = &scoreBoardPlayer1ScoreLabelObj;
    }
    else {
        playerScore = &player2Score;
        playerScoreLabelObj = &scoreBoardPlayer2ScoreLabelObj;
    }
    //Give points, change player and change questions
    (*playerScore)++;
    char *scoreAsString = getPlayerScoreAsString(*playerScore);
    if (!setLabelText(renderer, playerScoreLabelObj, scoreAsString, scoreFont, &orange)) {
        quit = true;
        retVal = false;
    }
    free(scoreAsString);
    return retVal;
}

void changePlayerTurn()
{
    if (currentPlayerTurnIndex == 2) {
        currentPlayerTurnIndex = 1;
    }
    else {
        currentPlayerTurnIndex++;
    }
}

bool changeToNextQuestion()
{
    currentQuestionIndex++;
    if (currentQuestionIndex < vectorGetSize(currentGameQuestions)) {
        Question *question = vectorGetItem(currentGameQuestions, currentQuestionIndex);
        if (!loadQuestionWithAnswers(question)) {
            return false;
        }
    }
    else {
        moveToEnd();
    }
    return true;
}

void moveToEnd()
{
    currentGameMode = endGame;
    currentInputMode = ChooseBool;
    freeQuestions();
    freeAnswers();
    char endGameMessage[DESCRIPTION_MAX] = { "The game is a tie!" };
    if (player1Score != player2Score) {
        sprintf(endGameMessage, "%s has won the game! Congratulations!", (player1Score > player2Score) ? player1Name : player2Name);
    }

    if (!setLabelText(renderer, &endGameMessageLabelObj, endGameMessage, playerNameEditFont, &white)) {
        quit = true;
        return;
    }
    if (!setLabelText(renderer, &endGameKeepSameUsersLabelObj, "Do you want to keep the same players for the next game? (y/n)", playerNameEditFont, &white)) {
        quit = true;
        return;
    }
}