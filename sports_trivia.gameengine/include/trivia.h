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

DataQueryResult *extractQuestionList(sqlite3_stmt *res);
bool loadRandomQuestionsFromDatabase(unsigned int count);

#endif