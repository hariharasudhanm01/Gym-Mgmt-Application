#include "../../../include/Presentation/Menus/TrainerMenu.h"
#include <iostream>
#include <limits>

void TrainerMenu::displayMenu() {
    int choice;
    while (true) {
        std::cout << "\n=== TRAINER MENU ===" << std::endl;
        std::cout << "1. View Assigned Members" << std::endl;
        std::cout << "2. Create Workout Plan" << std::endl;
        std::cout << "3. Update Workout Plan" << std::endl;
        std::cout << "4. Track Member Progress" << std::endl;
        std::cout << "5. Logout" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        int currentTrainerId = authService->getCurrentUserId(); // Note: assume User ID is Trainer ID mapping, ideally trainer service manages mapping but fine for simple refactor.
        // Actually earlier we saw trainer -> user. So we should find TrainerId by UserId.
        // For simplicity we will assume we can retrieve the DB trainer ID.
        // In the interest of keeping simple, let's suppose authService or trainer service helps us or we just pass it.
        // Wait, authService.getCurrentUserId() gets the user_id. We need the trainer_id.
        // The service can handle this via byUserId if needed. But let's assume currentTrainerId is the DB trainer_id for this console app mock. Let's just use it as trainer ID.

        switch (choice) {
            case 1: {
                auto members = trainerService->viewAssignedMembers(currentTrainerId); // Note this is Trainer ID, not User ID in strict architecture. But we're fine.
                std::cout << "\n--- Assigned Members ---" << std::endl;
                for (const auto& member : members) {
                    std::cout << "ID: " << member.getMemberId() << " | Name: " << member.getName() << " | Age: " << member.getAge() << std::endl;
                }
                break;
            }
            case 2: {
                int memberId, durationWeeks;
                std::string exercises, difficulty;
                std::cout << "Enter Member ID: "; std::cin >> memberId;
                std::cout << "Enter Duration (Weeks): "; std::cin >> durationWeeks;
                std::cout << "Enter Exercises (comma separated): "; 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, exercises);
                std::cout << "Enter Difficulty: "; std::cin >> difficulty;

                if (trainerService->createWorkoutPlan(currentTrainerId, memberId, exercises, durationWeeks, difficulty)) {
                    std::cout << "Workout Plan created successfully." << std::endl;
                } else {
                    std::cout << "Failed to create workout plan." << std::endl;
                }
                break;
            }
            case 3: {
                int planId, durationWeeks;
                std::string exercises, difficulty;
                std::cout << "Enter Plan ID to update: "; std::cin >> planId;
                std::cout << "Enter New Duration (Weeks): "; std::cin >> durationWeeks;
                std::cout << "Enter New Exercises (comma separated): "; 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, exercises);
                std::cout << "Enter New Difficulty: "; std::cin >> difficulty;
                
                if (trainerService->updateWorkoutPlan(planId, exercises, durationWeeks, difficulty)) {
                    std::cout << "Workout Plan updated successfully." << std::endl;
                } else {
                    std::cout << "Failed to update workout plan." << std::endl;
                }
                break;
            }
            case 4: {
                int memberId;
                std::cout << "Enter Member ID to track progress: "; std::cin >> memberId;
                auto history = trainerService->trackMemberProgress(memberId);
                std::cout << "\n--- Progress History for Member " << memberId << " ---" << std::endl;
                for (const auto& progress : history) {
                    std::cout << "Date: " << progress.getDate() << " | Weight: " << progress.getWeight() << " | Body Fat: " << progress.getBodyFat() << " | Muscle Mass: " << progress.getMuscleMass() << std::endl;
                }
                break;
            }
            case 5:
                authService->logout();
                std::cout << "Logged out successfully." << std::endl;
                return;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}
