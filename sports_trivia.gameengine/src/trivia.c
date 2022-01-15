#include "vector.h"
#include "trivia.h"
#include <stdio.h>
#include <string.h>

#define CVECTOR_LOGARITHMIC_GROWTH

void extractQuestionItem(vector *vec, sqlite3_stmt *res)
{
    Question *q = malloc(sizeof(Question));
    q->id = sqlite3_column_int(res, 0);
    strcpy(q->description, sqlite3_column_text(res, 1));
    q->rightAnswerNo = sqlite3_column_int(res, 2);
    vectorPushBack(vec, q);  
}

void extractAnswerItem(vector *vec, sqlite3_stmt *res)
{
    Answer *a = malloc(sizeof(Answer));
    a->id = sqlite3_column_int(res, 0);
    a->questionId = sqlite3_column_int(res, 1);
    a->no = sqlite3_column_int(res, 2);
    strcpy(a->description, sqlite3_column_text(res, 3));
    vectorPushBack(vec, a);
}

vector *loadRandomQuestionsFromDatabase(unsigned int count)
{
    char query[255];
    sprintf(query, "SELECT * FROM Question ORDER BY RANDOM() LIMIT %d", count);
    vector *result = getQueryData(query, extractQuestionItem);
    return result;
}

vector *loadAnswersFromQuestionId(int questionId)
{
    char query[255];
    sprintf(query, "SELECT * FROM Answer WHERE qid = %d ORDER BY no", questionId);
    vector *result = getQueryData(query, extractAnswerItem);
    return result;
}
