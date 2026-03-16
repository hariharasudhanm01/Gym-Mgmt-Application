#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../../Application/Services/AuthService.h"
#include "../../Application/Services/AdminService.h"
#include "../../Application/Services/TrainerService.h"
#include "../../Application/Services/MemberService.h"

class MainMenu {
private:
    AuthService* authService;
    AdminService* adminService;
    TrainerService* trainerService;
    MemberService* memberService;

public:
    MainMenu(AuthService* auth, AdminService* admin, TrainerService* trainer, MemberService* member)
        : authService(auth), adminService(admin), trainerService(trainer), memberService(member) {}

    void displayMenu();
    void loginFlow();
    void registerFlow();
};

#endif
