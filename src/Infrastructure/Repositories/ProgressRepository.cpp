#include "../../../include/Infrastructure/Repositories/ProgressRepository.h"
#include "../../../include/Infrastructure/Database/DatabaseManager.h"

HealthProgress ProgressRepository::getById(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT progress_id, member_id, weight, body_fat, muscle_mass, date "
                        "FROM HealthProgress WHERE progress_id = " + std::to_string(id);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    HealthProgress progress;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        progress.setProgressId(sqlite3_column_int(stmt, 0));
        progress.setMemberId(sqlite3_column_int(stmt, 1));
        progress.setWeight(sqlite3_column_double(stmt, 2));
        progress.setBodyFat(sqlite3_column_double(stmt, 3));
        progress.setMuscleMass(sqlite3_column_double(stmt, 4));
        if (sqlite3_column_text(stmt, 5)) progress.setDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
    }
    db->finalizeStatement(stmt);
    return progress;
}

std::vector<HealthProgress> ProgressRepository::getAll() {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT progress_id, member_id, weight, body_fat, muscle_mass, date FROM HealthProgress";
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<HealthProgress> records;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        HealthProgress progress;
        progress.setProgressId(sqlite3_column_int(stmt, 0));
        progress.setMemberId(sqlite3_column_int(stmt, 1));
        progress.setWeight(sqlite3_column_double(stmt, 2));
        progress.setBodyFat(sqlite3_column_double(stmt, 3));
        progress.setMuscleMass(sqlite3_column_double(stmt, 4));
        if (sqlite3_column_text(stmt, 5)) progress.setDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        records.push_back(progress);
    }
    db->finalizeStatement(stmt);
    return records;
}

std::vector<HealthProgress> ProgressRepository::getByMemberId(int memberId) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT progress_id, member_id, weight, body_fat, muscle_mass, date "
                        "FROM HealthProgress WHERE member_id = " + std::to_string(memberId);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<HealthProgress> records;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        HealthProgress progress;
        progress.setProgressId(sqlite3_column_int(stmt, 0));
        progress.setMemberId(sqlite3_column_int(stmt, 1));
        progress.setWeight(sqlite3_column_double(stmt, 2));
        progress.setBodyFat(sqlite3_column_double(stmt, 3));
        progress.setMuscleMass(sqlite3_column_double(stmt, 4));
        if (sqlite3_column_text(stmt, 5)) progress.setDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        records.push_back(progress);
    }
    db->finalizeStatement(stmt);
    return records;
}

bool ProgressRepository::add(const HealthProgress& progress) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "INSERT INTO HealthProgress (member_id, weight, body_fat, muscle_mass, date) VALUES (" +
                        std::to_string(progress.getMemberId()) + ", " +
                        std::to_string(progress.getWeight()) + ", " +
                        std::to_string(progress.getBodyFat()) + ", " +
                        std::to_string(progress.getMuscleMass()) + ", '" +
                        progress.getDate() + "')";
    return db->executeQuery(query);
}

bool ProgressRepository::update(const HealthProgress& progress) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "UPDATE HealthProgress SET "
                        "member_id = " + std::to_string(progress.getMemberId()) + ", "
                        "weight = " + std::to_string(progress.getWeight()) + ", "
                        "body_fat = " + std::to_string(progress.getBodyFat()) + ", "
                        "muscle_mass = " + std::to_string(progress.getMuscleMass()) + ", "
                        "date = '" + progress.getDate() + "' "
                        "WHERE progress_id = " + std::to_string(progress.getProgressId());
    return db->executeQuery(query);
}

bool ProgressRepository::remove(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "DELETE FROM HealthProgress WHERE progress_id = " + std::to_string(id);
    return db->executeQuery(query);
}
