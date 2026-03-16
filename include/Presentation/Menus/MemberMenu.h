#ifndef MEMBER_MENU_H
#define MEMBER_MENU_H

#include "../../Application/Services/MemberService.h"
#include "../../Application/Services/AuthService.h"

class MemberMenu {
private:
    MemberService* memberService;
    AuthService* authService;

public:
    MemberMenu(MemberService* mService, AuthService* aService) : memberService(mService), authService(aService) {}
    void displayMenu();
};

#endif
