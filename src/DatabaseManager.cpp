#include "../include/DatabaseManager.h"
#include "../libs/sqlite/sqlite3.h"
#include <iostream>
#include <cstring>

DatabaseManager::DatabaseManager() : db(nullptr) {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

bool DatabaseManager::openDatabase(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &db);
    
    if (rc) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    std::cout << "Database opened successfully: " << dbName << std::endl;
    
    if (!createTables()) {
        return false;
    }
    
    return true;
}

void DatabaseManager::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::executeQuery(const std::string& query) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

bool DatabaseManager::executeQueryWithCallback(const std::string& query, 
                                               int (*callback)(void*, int, char**, char**)) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), callback, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

sqlite3_stmt* DatabaseManager::prepareStatement(const std::string& query) {
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    
    return stmt;
}

void DatabaseManager::finalizeStatement(sqlite3_stmt* stmt) {
    if (stmt) {
        sqlite3_finalize(stmt);
    }
}

std::string DatabaseManager::getLastError() {
    return std::string(sqlite3_errmsg(db));
}

bool DatabaseManager::createTables() {
    const char* schema = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            role INTEGER NOT NULL,
            createdDate TEXT,
            active INTEGER DEFAULT 1
        );
        
        CREATE TABLE IF NOT EXISTS members (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            age INTEGER,
            gender TEXT,
            height REAL,
            weight REAL,
            membershipType TEXT,
            joinDate TEXT,
            expiryDate TEXT,
            active INTEGER DEFAULT 1,
            FOREIGN KEY(id) REFERENCES users(id)
        );
        
        CREATE TABLE IF NOT EXISTS healthRecords (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            memberId INTEGER NOT NULL,
            height REAL,
            weight REAL,
            bmi REAL,
            category TEXT,
            recordDate TEXT,
            FOREIGN KEY(memberId) REFERENCES members(id)
        );
        
        CREATE TABLE IF NOT EXISTS workoutPlans (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            memberId INTEGER NOT NULL,
            planName TEXT NOT NULL,
            difficulty TEXT,
            createdDate TEXT,
            active INTEGER DEFAULT 1,
            FOREIGN KEY(memberId) REFERENCES members(id)
        );
        
        CREATE TABLE IF NOT EXISTS exercises (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            planId INTEGER NOT NULL,
            name TEXT NOT NULL,
            sets INTEGER,
            reps INTEGER,
            description TEXT,
            muscleGroup TEXT,
            FOREIGN KEY(planId) REFERENCES workoutPlans(id)
        );
        
        CREATE TABLE IF NOT EXISTS progressRecords (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            memberId INTEGER NOT NULL,
            weight REAL,
            bmi REAL,
            achievement TEXT,
            recordDate TEXT,
            FOREIGN KEY(memberId) REFERENCES members(id)
        );
    )";
    
    return executeQuery(schema);
}
