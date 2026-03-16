#include "../../../include/Application/Services/AuthService.h"
#include "../../../include/Domain/Entities/Admin.h"
#include <iostream>

bool AuthService::login(const std::string& email, const std::string& password) {
    auto user = userRepository.getByEmail(email);
    if (user && user->getPassword() == password) {
        currentUserId = user->getUserId();
        currentUserRole = user->getRole();
        currentUsername = user->getName();
        return true;
    }
    return false;
}

void AuthService::logout() {
    currentUserId = 0;
    currentUsername = "";
}

bool AuthService::registerAdmin(const std::string& name, const std::string& email, const std::string& phone, const std::string& password) {
    std::unique_ptr<User> user = std::make_unique<Admin>(0, name, email, phone, password);
    return userRepository.add(user);
}
