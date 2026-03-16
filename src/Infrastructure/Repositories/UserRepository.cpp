#include "../../../include/Infrastructure/Repositories/UserRepository.h"
#include "../../../include/Infrastructure/Database/DatabaseManager.h"
#include "../../../include/Infrastructure/Factories/UserFactory.h"
#include <iostream>

UserRepository::UserRepository() {}

std::unique_ptr<User> UserRepository::getById(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT user_id, name, email, phone, password, role FROM Users WHERE user_id = " + std::to_string(id);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::unique_ptr<User> user = nullptr;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        Role role = static_cast<Role>(sqlite3_column_int(stmt, 5));
        user = UserFactory::createUser(role);
        if (user) {
            user->setUserId(sqlite3_column_int(stmt, 0));
            user->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            user->setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            user->setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            user->setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        }
    }
    db->finalizeStatement(stmt);
    return user;
}

std::unique_ptr<User> UserRepository::getByEmail(const std::string& email) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT user_id, name, email, phone, password, role FROM Users WHERE email = '" + email + "'";
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::unique_ptr<User> user = nullptr;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        Role role = static_cast<Role>(sqlite3_column_int(stmt, 5));
        user = UserFactory::createUser(role);
        if (user) {
            user->setUserId(sqlite3_column_int(stmt, 0));
            user->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            user->setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            user->setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            user->setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        }
    }
    db->finalizeStatement(stmt);
    return user;
}

std::vector<std::unique_ptr<User>> UserRepository::getAll() {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT user_id, name, email, phone, password, role FROM Users";
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<std::unique_ptr<User>> users;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        Role role = static_cast<Role>(sqlite3_column_int(stmt, 5));
        auto user = UserFactory::createUser(role);
        if (user) {
            user->setUserId(sqlite3_column_int(stmt, 0));
            user->setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            user->setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            user->setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            user->setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            users.push_back(std::move(user));
        }
    }
    db->finalizeStatement(stmt);
    return users;
}

bool UserRepository::add(const std::unique_ptr<User>& user) {
    if (!user) return false;
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "INSERT INTO Users (name, email, phone, password, role) VALUES ('" +
                        user->getName() + "', '" + user->getEmail() + "', '" + user->getPhone() + "', '" +
                        user->getPassword() + "', " + std::to_string(static_cast<int>(user->getRole())) + ")";
    
    bool result = db->executeQuery(query);
    if(result) {
        std::string getIdQuery = "SELECT last_insert_rowid()";
        sqlite3_stmt* stmt = db->prepareStatement(getIdQuery);
        if(stmt && sqlite3_step(stmt) == SQLITE_ROW) {
            user->setUserId(sqlite3_column_int(stmt, 0));
        }
        db->finalizeStatement(stmt);
    }
    return result;
}

bool UserRepository::update(const std::unique_ptr<User>& user) {
    if (!user) return false;
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "UPDATE Users SET name = '" + user->getName() +
                        "', email = '" + user->getEmail() +
                        "', phone = '" + user->getPhone() +
                        "', password = '" + user->getPassword() +
                        "', role = " + std::to_string(static_cast<int>(user->getRole())) +
                        " WHERE user_id = " + std::to_string(user->getUserId());
    return db->executeQuery(query);
}

bool UserRepository::remove(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "DELETE FROM Users WHERE user_id = " + std::to_string(id);
    return db->executeQuery(query);
}
