#include "sqlitedb.h"
#include <iostream>

int main()
{
    SQLiteDB sqlite("NowaBaza.db");
    if (!sqlite.open())
        return SQLITE_CANTOPEN;

    SQLiteDB::QueryResult queryResult;

    std::string createQuery =
        "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, age INTEGER); "
        "SELECT * FROM users";

    if (!sqlite.exec(createQuery, queryResult))
        return SQLITE_ERROR;

    for (const auto &row : queryResult)
    {
        for (const auto &[name, value] : row)
        {
            std::cout << name << ": " << value << ". ";
        }
        std::cout << "\n";
    }
}
