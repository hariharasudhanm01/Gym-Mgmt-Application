#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include "../../Infrastructure/Repositories/UserRepository.h"
#include <memory>
#include <string>

class AuthService {
private:
    UserRepository userRepository;
    int currentUserId;
    Role currentUserRole;
    std::string currentUsername;

public:
    AuthService() : currentUserId(0) {}

    bool login(const std::string& email, const std::string& password);
    void logout();

    bool registerAdmin(const std::string& name, const std::string& email, const std::string& phone, const std::string& password);
    
    int getCurrentUserId() const { return currentUserId; }
    Role getCurrentRole() const { return currentUserRole; }
    std::string getCurrentUsername() const { return currentUsername; }
    bool isLoggedIn() const { return currentUserId > 0; }
};

#endif
