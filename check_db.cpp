#include <iostream>
#include <iomanip>
#include "libs/sqlite/sqlite3.h"

// Callback to print sqlite rows
static int print_row(void* NotUsed, int argc, char** argv, char** azColName) {
    for(int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    std::cout << "\n";
    return 0;
}

void check_table(sqlite3* db, const char* tableName) {
    std::cout << "\n--- Table: " << tableName << " ---\n";
    char* errMsg = 0;
    std::string query = std::string("SELECT * FROM ") + tableName + ";";
    int rc = sqlite3_exec(db, query.c_str(), print_row, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("gym_management.db", &db);
    if(rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        return 0;
    } else {
        std::cout << "Opened database successfully\n";
    }

    const char* tables[] = {"Users", "Members", "Trainers", "WorkoutPlans", "HealthProgress", "TrainerRatings"};
    for(const char* table : tables) {
        check_table(db, table);
    }

    sqlite3_close(db);
    return 0;
}
