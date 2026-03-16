#include <iostream>
#include <memory>
#include "include/Infrastructure/Database/DatabaseManager.h"
#include "include/Application/Strategies/AverageRatingStrategy.h"
#include "include/Application/Services/AuthService.h"
#include "include/Application/Services/AdminService.h"
#include "include/Application/Services/TrainerService.h"
#include "include/Application/Services/MemberService.h"
#include "include/Presentation/Menus/MainMenu.h"

int main() {
    // 1. Initialize Database (Singleton)
    DatabaseManager* db = DatabaseManager::getInstance();
    if (!db->openDatabase("gym_management.db")) {
        std::cerr << "Failed to initialize database." << std::endl;
        return 1;
    }

    // 2. Initialize Strategy
    AverageRatingStrategy avgRatingStrategy;

    // 3. Initialize Services
    AuthService authService;
    AdminService adminService;
    TrainerService trainerService;
    MemberService memberService(&avgRatingStrategy);

    // 4. Initialize Main Menu and Start Application Loop
    MainMenu mainMenu(&authService, &adminService, &trainerService, &memberService);
    mainMenu.displayMenu();

    // Cleanup
    db->closeDatabase();
    return 0;
}