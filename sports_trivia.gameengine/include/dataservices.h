#ifndef DATASERVICES_H
#define DATASERVICES_H

#include "vector.h"
#include <sqlite3.h>
#include <stdbool.h>
#include <stdlib.h>

sqlite3 *db;
void initializeDatabase();
bool databaseOpen(const char *dbPath);
void databaseClose(sqlite3 *db);

vector *getQueryData(const char *sqlQuery, void(*extractItem)(vector *vec, sqlite3_stmt *res));
const char *getLastDatabaseErrorMsg();
#endif