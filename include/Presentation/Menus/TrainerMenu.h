#ifndef TRAINER_MENU_H
#define TRAINER_MENU_H

#include "../../Application/Services/TrainerService.h"
#include "../../Application/Services/AuthService.h"

class TrainerMenu {
private:
    TrainerService* trainerService;
    AuthService* authService;

public:
    TrainerMenu(TrainerService* tService, AuthService* aService) : trainerService(tService), authService(aService) {}
    void displayMenu();
};

#endif
