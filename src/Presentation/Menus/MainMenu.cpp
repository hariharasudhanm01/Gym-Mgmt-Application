#include "../../../include/Presentation/Menus/MainMenu.h"
#include "../../../include/Presentation/Menus/AdminMenu.h"
#include "../../../include/Presentation/Menus/TrainerMenu.h"
#include "../../../include/Presentation/Menus/MemberMenu.h"
#include <iostream>

void MainMenu::displayMenu() {
    int choice;
    while (true) {
        std::cout << "\n=== GYM MANAGEMENT SYSTEM ===" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Register Admin (First Setup)" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                loginFlow();
                break;
            case 2:
                registerFlow();
                break;
            case 3:
                std::cout << "Exiting system. Goodbye!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}

void MainMenu::loginFlow() {
    std::string email, password;
    std::cout << "Enter Email: "; std::cin >> email;
    std::cout << "Enter Password: "; std::cin >> password;

    if (authService->login(email, password)) {
        std::cout << "Login successful. Welcome, " << authService->getCurrentUsername() << "!" << std::endl;
        
        if (authService->getCurrentRole() == Role::Admin) {
            AdminMenu adminMenu(adminService, authService);
            adminMenu.displayMenu();
        } else if (authService->getCurrentRole() == Role::Trainer) {
            TrainerMenu trainerMenu(trainerService, authService);
            trainerMenu.displayMenu();
        } else if (authService->getCurrentRole() == Role::Member) {
            MemberMenu memberMenu(memberService, authService);
            memberMenu.displayMenu();
        }
    } else {
        std::cout << "Login failed. Please check credentials." << std::endl;
    }
}

void MainMenu::registerFlow() {
    std::string name, email, phone, password;
    std::cout << "Enter Admin Name: "; std::cin >> name;
    std::cout << "Enter Admin Email: "; std::cin >> email;
    std::cout << "Enter Admin Phone: "; std::cin >> phone;
    std::cout << "Enter Admin Password: "; std::cin >> password;

    if(authService->registerAdmin(name, email, phone, password)) {
        std::cout << "Admin registered successfully." << std::endl;
    } else {
        std::cout << "Failed to register Admin." << std::endl;
    }
}
