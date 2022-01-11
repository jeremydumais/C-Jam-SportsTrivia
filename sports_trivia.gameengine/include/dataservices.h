#ifndef DATASERVICES_H
#define DATASERVICES_H

#include <sqlite3.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    void *elements;
    int count;
} DataQueryResult;

sqlite3 *db;
void initializeDatabase();
bool databaseOpen(const char *dbPath);
void databaseClose(sqlite3 *db);

DataQueryResult *getQueryData(const char *sqlQuery, DataQueryResult *(*readDataFun)(sqlite3_stmt *res));
const char *getLastDatabaseErrorMsg();
#endif