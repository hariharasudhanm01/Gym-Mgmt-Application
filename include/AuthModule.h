#ifndef AUTH_MODULE_H
#define AUTH_MODULE_H

#include <string>
#include "DatabaseManager.h"

enum UserRole { MEMBER = 1, TRAINER = 2, ADMIN = 3 };

class AuthModule {
private:
    DatabaseManager& db;
    int currentUserId;
    UserRole currentUserRole;
    std::string currentUsername;
    
public:
    AuthModule(DatabaseManager& database);
    
    bool registerUser(const std::string& username, const std::string& password, UserRole role);
    bool registerMember(const std::string& username, const std::string& password, 
                       const std::string& name, int age, const std::string& gender,
                       double height, double weight, const std::string& membershipType);
    bool login(const std::string& username, const std::string& password);
    bool logout();
    void displayLoginMenu();
    void displayRegistrationMenu();
    
    int getCurrentUserId() const { return currentUserId; }
    UserRole getCurrentRole() const { return currentUserRole; }
    std::string getCurrentUsername() const { return currentUsername; }
    bool isLoggedIn() const { return currentUserId > 0; }
    
private:
    std::string hashPassword(const std::string& password);
};

#endif
