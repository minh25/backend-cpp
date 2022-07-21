#include <sqlite3.h>
#include <iostream>
#include <sstream>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  for (int i = 0; i < argc; i++)
  {
    std::cout << azColName[i] << (argv[i] ? argv[i] : "NULL") << std::endl;
  }

  return 0;
}

int main(int argc, char const *argv[])
{
  sqlite3 *db;
  char *zErrMsg = nullptr;
  int rc;
  char *sql;

  rc = sqlite3_open("test.db", &db);

  if (rc)
  {
    std::cout << sqlite3_errmsg(db);
    return 0;
  }
  else
  {
    std::cout << "Connect successfully" << std::endl;
  }

  sql = "CREATE TABLE COMPANY("
        "ID INT PRIMARY KEY     NOT NULL,"
        "NAME           TEXT    NOT NULL,"
        "AGE            INT     NOT NULL,"
        "ADDRESS        CHAR(50),"
        "SALARY         REAL );";

  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  else
  {
    fprintf(stdout, "Successfully\n");
  }
  sqlite3_close(db);
  return 0;
}