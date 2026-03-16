#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>
#include <mutex>
#include "../../../libs/sqlite/sqlite3.h"

class DatabaseManager {
private:
    static DatabaseManager* instance;
    sqlite3* db;
    
    // Private constructor for Singleton
    DatabaseManager();
    ~DatabaseManager();

public:
    // Delete copy constructor and assignment operator
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // Singleton access method
    static DatabaseManager* getInstance();

    bool openDatabase(const std::string& dbName);
    void closeDatabase();
    bool executeQuery(const std::string& query);
    bool executeQueryWithCallback(const std::string& query, int (*callback)(void*, int, char**, char**), void* data = nullptr);
    sqlite3_stmt* prepareStatement(const std::string& query);
    void finalizeStatement(sqlite3_stmt* stmt);
    sqlite3* getDatabase() { return db; }
    std::string getLastError();

private:
    bool createTables();
};

#endif
