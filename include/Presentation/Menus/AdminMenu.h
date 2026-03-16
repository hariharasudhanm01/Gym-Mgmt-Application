#ifndef ADMIN_MENU_H
#define ADMIN_MENU_H

#include "../../Application/Services/AdminService.h"
#include "../../Application/Services/AuthService.h"

class AdminMenu {
private:
    AdminService* adminService;
    AuthService* authService;

public:
    AdminMenu(AdminService* aService, AuthService* auth) : adminService(aService), authService(auth) {}
    void displayMenu();
};

#endif
