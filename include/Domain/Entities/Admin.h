#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <iostream>

class Admin : public User {
public:
    Admin() : User() {
        this->role = Role::Admin;
    }
    
    Admin(int uId, const std::string& n, const std::string& e, const std::string& p, const std::string& pwd)
        : User(uId, n, e, p, pwd, Role::Admin) {}

    void login() override {
        std::cout << "Admin " << name << " logged in." << std::endl;
    }
    
    void logout() override {
        std::cout << "Admin " << name << " logged out." << std::endl;
    }
};

#endif
