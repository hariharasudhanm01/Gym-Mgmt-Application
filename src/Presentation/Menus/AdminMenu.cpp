#include "../../../include/Presentation/Menus/AdminMenu.h"
#include <iostream>
#include <limits>

void AdminMenu::displayMenu() {
    int choice;
    while (true) {
        std::cout << "\n=== ADMIN MENU ===" << std::endl;
        std::cout << "1. Add Member" << std::endl;
        std::cout << "2. Remove Member" << std::endl;
        std::cout << "3. Add Trainer" << std::endl;
        std::cout << "4. Remove Trainer" << std::endl;
        std::cout << "5. Assign Trainer to Member" << std::endl;
        std::cout << "6. View Reports" << std::endl;
        std::cout << "7. Run System Tests" << std::endl;
        std::cout << "8. Logout" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, email, phone, password, type;
                int age; double h, w;
                std::cout << "Enter name: "; std::cin >> name;
                std::cout << "Enter email: "; std::cin >> email;
                std::cout << "Enter phone: "; std::cin >> phone;
                std::cout << "Enter password: "; std::cin >> password;
                std::cout << "Enter age: "; std::cin >> age;
                std::cout << "Enter height (cm): "; std::cin >> h;
                std::cout << "Enter weight (kg): "; std::cin >> w;
                std::cout << "Enter Membership Type (Gold/Silver): "; std::cin >> type;
                if(adminService->addMember(name, email, phone, password, age, h, w, type)) {
                    std::cout << "Member added successfully." << std::endl;
                } else {
                    std::cout << "Failed to add member." << std::endl;
                }
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter Member ID to remove: "; std::cin >> id;
                if(adminService->removeMember(id)) std::cout << "Removed." << std::endl;
                else std::cout << "Failed." << std::endl;
                break;
            }
            case 3: {
                std::string name, email, phone, password, spec;
                int expr;
                std::cout << "Enter name: "; std::cin >> name;
                std::cout << "Enter email: "; std::cin >> email;
                std::cout << "Enter phone: "; std::cin >> phone;
                std::cout << "Enter password: "; std::cin >> password;
                std::cout << "Enter Specialization: "; std::cin >> spec;
                std::cout << "Enter Experience Years: "; std::cin >> expr;
                if(adminService->addTrainer(name, email, phone, password, spec, expr)) {
                    std::cout << "Trainer added successfully." << std::endl;
                } else {
                    std::cout << "Failed to add trainer." << std::endl;
                }
                break;
            }
            case 4: {
                int id;
                std::cout << "Enter Trainer ID to remove: "; std::cin >> id;
                if(adminService->removeTrainer(id)) std::cout << "Removed." << std::endl;
                else std::cout << "Failed." << std::endl;
                break;
            }
            case 5: {
                int mId, tId;
                std::cout << "Enter Member ID: "; std::cin >> mId;
                std::cout << "Enter Trainer ID: "; std::cin >> tId;
                if(adminService->assignTrainerToMember(mId, tId)) std::cout << "Assigned." << std::endl;
                else std::cout << "Failed." << std::endl;
                break;
            }
            case 6:
                adminService->generateReports();
                break;
            case 7:
                std::cout << "\n--- Running System Tests ---" << std::endl;
                adminService->testDatabaseConnection();
                adminService->testUserCreation();
                adminService->testTrainerAssignment();
                adminService->testWorkoutPlanCreation();
                adminService->testProgressTracking();
                break;
            case 8:
                authService->logout();
                std::cout << "Logged out successfully." << std::endl;
                return;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}
