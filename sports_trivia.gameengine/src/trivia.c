#include "trivia.h"
#include <stdio.h>

DataQueryResult *extractQuestionList(sqlite3_stmt *res)
{
    DataQueryResult *retVal = malloc(sizeof(DataQueryResult));
    int rc = sqlite3_step(res);
    
    if (rc == SQLITE_ROW) {
        printf("%s\n", sqlite3_column_text(res, 1));
    }
    
    retVal->count = 15;
    return retVal; 
}

bool loadRandomQuestionsFromDatabase(unsigned int count)
{
    
    return false;
}