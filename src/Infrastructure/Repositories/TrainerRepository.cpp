#include "../../../include/Infrastructure/Repositories/TrainerRepository.h"
#include "../../../include/Infrastructure/Database/DatabaseManager.h"
#include <iostream>

Trainer TrainerRepository::getById(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT t.trainer_id, t.user_id, t.specialization, t.experience_years, t.rating, "
                        "u.name, u.email, u.phone, u.password "
                        "FROM Trainers t JOIN Users u ON t.user_id = u.user_id WHERE t.trainer_id = " + std::to_string(id);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    Trainer trainer;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        trainer.setTrainerId(sqlite3_column_int(stmt, 0));
        trainer.setUserId(sqlite3_column_int(stmt, 1));
        if(sqlite3_column_text(stmt, 2)) trainer.setSpecialization(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        trainer.setExperienceYears(sqlite3_column_int(stmt, 3));
        trainer.setRating(sqlite3_column_double(stmt, 4));
        if(sqlite3_column_text(stmt, 5)) trainer.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        if(sqlite3_column_text(stmt, 6)) trainer.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        if(sqlite3_column_text(stmt, 7)) trainer.setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        if(sqlite3_column_text(stmt, 8)) trainer.setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        trainer.setRole(Role::Trainer);
    }
    db->finalizeStatement(stmt);
    return trainer;
}

Trainer TrainerRepository::getByUserId(int userId) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT t.trainer_id, t.user_id, t.specialization, t.experience_years, t.rating, "
                        "u.name, u.email, u.phone, u.password "
                        "FROM Trainers t JOIN Users u ON t.user_id = u.user_id WHERE t.user_id = " + std::to_string(userId);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    Trainer trainer;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        trainer.setTrainerId(sqlite3_column_int(stmt, 0));
        trainer.setUserId(sqlite3_column_int(stmt, 1));
        if(sqlite3_column_text(stmt, 2)) trainer.setSpecialization(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        trainer.setExperienceYears(sqlite3_column_int(stmt, 3));
        trainer.setRating(sqlite3_column_double(stmt, 4));
        if(sqlite3_column_text(stmt, 5)) trainer.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        if(sqlite3_column_text(stmt, 6)) trainer.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        if(sqlite3_column_text(stmt, 7)) trainer.setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        if(sqlite3_column_text(stmt, 8)) trainer.setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        trainer.setRole(Role::Trainer);
    }
    db->finalizeStatement(stmt);
    return trainer;
}

std::vector<Trainer> TrainerRepository::getAll() {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT t.trainer_id, t.user_id, t.specialization, t.experience_years, t.rating, "
                        "u.name, u.email, u.phone, u.password "
                        "FROM Trainers t JOIN Users u ON t.user_id = u.user_id";
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<Trainer> trainers;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        Trainer trainer;
        trainer.setTrainerId(sqlite3_column_int(stmt, 0));
        trainer.setUserId(sqlite3_column_int(stmt, 1));
        if(sqlite3_column_text(stmt, 2)) trainer.setSpecialization(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        trainer.setExperienceYears(sqlite3_column_int(stmt, 3));
        trainer.setRating(sqlite3_column_double(stmt, 4));
        if(sqlite3_column_text(stmt, 5)) trainer.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        if(sqlite3_column_text(stmt, 6)) trainer.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        if(sqlite3_column_text(stmt, 7)) trainer.setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        if(sqlite3_column_text(stmt, 8)) trainer.setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        trainer.setRole(Role::Trainer);
        trainers.push_back(trainer);
    }
    db->finalizeStatement(stmt);
    return trainers;
}

bool TrainerRepository::add(const Trainer& trainer) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "INSERT INTO Trainers (user_id, specialization, experience_years, rating) VALUES (" +
                        std::to_string(trainer.getUserId()) + ", '" +
                        trainer.getSpecialization() + "', " +
                        std::to_string(trainer.getExperienceYears()) + ", " +
                        std::to_string(trainer.getRating()) + ")";
    return db->executeQuery(query);
}

bool TrainerRepository::update(const Trainer& trainer) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "UPDATE Trainers SET "
                        "specialization = '" + trainer.getSpecialization() + "', "
                        "experience_years = " + std::to_string(trainer.getExperienceYears()) + ", "
                        "rating = " + std::to_string(trainer.getRating()) + " "
                        "WHERE trainer_id = " + std::to_string(trainer.getTrainerId());
    return db->executeQuery(query);
}

bool TrainerRepository::remove(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "DELETE FROM Trainers WHERE trainer_id = " + std::to_string(id);
    return db->executeQuery(query);
}
