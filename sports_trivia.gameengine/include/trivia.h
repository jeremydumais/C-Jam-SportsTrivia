#ifndef QUESTION_H
#define QUESTION_H

#include "dataservices.h"
#include <stdbool.h>

#define DESCRIPTION_MAX 256

typedef struct {
    int id;
    char description[DESCRIPTION_MAX];
    int rightAnswerNo;
} Question;

typedef struct {
    int id;
    int questionId;
    int no;
    char description[DESCRIPTION_MAX];
} Answer;

vector *loadRandomQuestionsFromDatabase(unsigned int count);
vector *loadAnswersFromQuestionId(int questionId);

#endif