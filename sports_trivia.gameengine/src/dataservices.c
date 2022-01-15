#include "dataservices.h"

const char *DATABASEPATH = "sports_trivia/resources/trivia.db";

void initializeDatabase()
{
    db = NULL;
}

bool databaseOpen(const char *dbPath)
{
    int rc = sqlite3_open(dbPath, &db);
    return rc == SQLITE_OK;
}

void databaseClose(sqlite3 *db)
{
    sqlite3_close(db);
    db = NULL;
}

vector *extractList(sqlite3_stmt *res, void(*extractItem)(vector *vec, sqlite3_stmt *res))
{
    vector *retVal = malloc(sizeof(vector));
    vectorInit(retVal);
    int rc = sqlite3_step(res);
    
    while (rc == SQLITE_ROW) {
        extractItem(retVal, res);
        rc = sqlite3_step(res);
    }
    return retVal; 
}

vector *getQueryData(const char *sqlQuery, void(*extractItem)(vector *vec, sqlite3_stmt *res))
{
    if (!db && !databaseOpen(DATABASEPATH)) {
        databaseClose(db);
        return NULL;
    }
    sqlite3_stmt *res;
    int rc = sqlite3_prepare_v2(db, sqlQuery, -1, &res, 0);    
    
    if (rc != SQLITE_OK) {
        return NULL;
    }    
    vector *result = extractList(res, extractItem);
    sqlite3_finalize(res);
    return result;
}

const char *getLastDatabaseErrorMsg()
{
    return sqlite3_errmsg(db);
}
