#pragma once
#include "isqlengine.h"

class PersonManager
{
  private:
    ISQLEngine &db_;

    bool open() const
    {
        if (!db_.isOpen())
        {
            return db_.open();
        }
        return true;
    }

  public:
    PersonManager(ISQLEngine &db) : db_(db)
    {
    }

    bool addPerson(const std::string &name, int age)
    {
        if (!open())
        {
            return false; // Database not open
        }
        std::string query = "INSERT INTO persons (name, age) VALUES ('" + name + "', " + std::to_string(age) + ")";
        ISQLEngine::QueryResult result;
        return db_.exec(query, result);
    }
    ISQLEngine::QueryResult getPersons() const
    {
        if (!open())
        {
            return {}; // Database not open
        }
        ISQLEngine::QueryResult result;
        db_.exec("SELECT * FROM persons", result);
        return result;
    }
    int getPersonNumber() const
    {
        if (!open())
        {
            return false; // Database not open
        }
        std::string query = "SELECT COUNT(*) FROM persons";
        ISQLEngine::QueryResult result;
        if (db_.exec(query, result) && !result.empty())
        {
            const auto &row = result[0];
            auto it = std::find_if(row.begin(), row.end(), [](const auto &pair) { return pair.first == "COUNT(*)"; });
            if (it != row.end())
            {
                return std::stoi(it->second);
            }
        }
        return 0; // Person not found
    }
    bool deletePerson(const std::string &name)
    {
        if (!open())
        {
            return false; // Database not open
        }
        std::string query = "DELETE FROM persons WHERE name = '" + name + "'";
        ISQLEngine::QueryResult result;
        return db_.exec(query, result);
    }
};
