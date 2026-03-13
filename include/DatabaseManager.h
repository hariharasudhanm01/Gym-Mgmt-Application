#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>
#include <vector>

extern "C" {
    struct sqlite3;
    struct sqlite3_stmt;
}

class DatabaseManager {
private:
    sqlite3* db;
    
public:
    DatabaseManager();
    ~DatabaseManager();
    
    bool openDatabase(const std::string& dbName);
    void closeDatabase();
    bool executeQuery(const std::string& query);
    bool executeQueryWithCallback(const std::string& query, int (*callback)(void*, int, char**, char**));
    sqlite3_stmt* prepareStatement(const std::string& query);
    void finalizeStatement(sqlite3_stmt* stmt);
    sqlite3* getDatabase() { return db; }
    bool createTables();
    std::string getLastError();
};

#endif
