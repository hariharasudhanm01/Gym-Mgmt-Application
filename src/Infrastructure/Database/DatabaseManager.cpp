#include "../../../include/Infrastructure/Database/DatabaseManager.h"
#include <iostream>
#include <cstring>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() : db(nullptr) {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
    return instance;
}

bool DatabaseManager::openDatabase(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &db);
    
    if (rc) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    if (!createTables()) {
        std::cerr << "Error creating tables." << std::endl;
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
                                               int (*callback)(void*, int, char**, char**), void* data) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), callback, data, &errMsg);
    
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
    if (db) return std::string(sqlite3_errmsg(db));
    return "Database not open";
}

bool DatabaseManager::createTables() {
    const char* schema = R"(
        CREATE TABLE IF NOT EXISTS Users (
            user_id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT UNIQUE,
            phone TEXT,
            password TEXT NOT NULL,
            role INTEGER NOT NULL
        );
        
        CREATE TABLE IF NOT EXISTS Members (
            member_id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            age INTEGER,
            height REAL,
            weight REAL,
            trainer_id INTEGER,
            membership_type TEXT,
            FOREIGN KEY(user_id) REFERENCES Users(user_id)
        );
        
        CREATE TABLE IF NOT EXISTS Trainers (
            trainer_id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            specialization TEXT,
            experience_years INTEGER,
            rating REAL DEFAULT 0.0,
            FOREIGN KEY(user_id) REFERENCES Users(user_id)
        );

        CREATE TABLE IF NOT EXISTS WorkoutPlans (
            plan_id INTEGER PRIMARY KEY AUTOINCREMENT,
            member_id INTEGER NOT NULL,
            trainer_id INTEGER NOT NULL,
            exercise_list TEXT,
            duration_weeks INTEGER,
            difficulty_level TEXT,
            FOREIGN KEY(member_id) REFERENCES Members(member_id),
            FOREIGN KEY(trainer_id) REFERENCES Trainers(trainer_id)
        );
        
        CREATE TABLE IF NOT EXISTS HealthProgress (
            progress_id INTEGER PRIMARY KEY AUTOINCREMENT,
            member_id INTEGER NOT NULL,
            weight REAL,
            body_fat REAL,
            muscle_mass REAL,
            date TEXT,
            FOREIGN KEY(member_id) REFERENCES Members(member_id)
        );

        CREATE TABLE IF NOT EXISTS TrainerRatings (
            rating_id INTEGER PRIMARY KEY AUTOINCREMENT,
            trainer_id INTEGER NOT NULL,
            member_id INTEGER NOT NULL,
            rating_score REAL NOT NULL,
            review TEXT,
            FOREIGN KEY(trainer_id) REFERENCES Trainers(trainer_id),
            FOREIGN KEY(member_id) REFERENCES Members(member_id)
        );
    )";
    
    return executeQuery(schema);
}
