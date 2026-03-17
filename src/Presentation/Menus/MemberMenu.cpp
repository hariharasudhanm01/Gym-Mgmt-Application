#include "../../../include/Presentation/Menus/MemberMenu.h"
#include <iostream>

void MemberMenu::displayMenu() {
    int choice;
    while (true) {
        std::cout << "\n=== MEMBER MENU ===" << std::endl;
        std::cout << "1. View Workout Plan" << std::endl;
        std::cout << "2. Track Health Progress" << std::endl;
        std::cout << "3. View Progress History" << std::endl;
        std::cout << "4. Choose Trainer based on rating" << std::endl;
        std::cout << "5. Rate Trainer" << std::endl;
        std::cout << "6. Calculate BMI" << std::endl;
        std::cout << "7. Logout" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        int currentUserId = authService->getCurrentUserId();

        switch (choice) {
            case 1: {
                auto plans = memberService->viewWorkoutPlan(currentUserId);
                std::cout << "\n--- Workout Plans ---" << std::endl;
                for (const auto& plan : plans) {
                    std::cout << "Plan ID: " << plan.getPlanId() << " | Exercises: " << plan.getExerciseList() << " | Difficulty: " << plan.getDifficultyLevel() << std::endl;
                }
                break;
            }
            case 2: {
                double weight, bodyFat, muscleMass;
                std::string date;
                std::cout << "Enter weight (kg): "; std::cin >> weight;
                std::cout << "Enter body fat %: "; std::cin >> bodyFat;
                std::cout << "Enter muscle mass (kg): "; std::cin >> muscleMass;
                std::cout << "Enter date (YYYY-MM-DD): "; std::cin >> date;
                
                if(memberService->updateHealthMetrics(currentUserId, weight, bodyFat, muscleMass, date)) {
                    std::cout << "Health metrics updated successfully." << std::endl;
                } else {
                    std::cout << "Failed to update health metrics." << std::endl;
                }
                break;
            }
            case 3: {
                auto history = memberService->viewHealthProgress(currentUserId);
                std::cout << "\n--- Health Progress History ---" << std::endl;
                for (const auto& progress : history) {
                    std::cout << "Date: " << progress.getDate() << " | Weight: " << progress.getWeight() << " | Body Fat: " << progress.getBodyFat() << " | Muscle Mass: " << progress.getMuscleMass() << std::endl;
                }
                break;
            }
            case 4: {
                auto trainers = memberService->viewTrainerRatings();
                std::cout << "\n--- Available Trainers ---" << std::endl;
                for (const auto& trainer : trainers) {
                    std::cout << "ID: " << trainer.getTrainerId() << " | Name: " << trainer.getName() << " | Rating: " << trainer.getRating() << " | Spec: " << trainer.getSpecialization() << std::endl;
                }
                int trainerId;
                std::cout << "Enter Trainer ID to choose: "; std::cin >> trainerId;
                if(memberService->chooseTrainerBasedOnRating(currentUserId, trainerId)) {
                    std::cout << "Trainer successfully assigned!" << std::endl;
                } else {
                    std::cout << "Failed to assign trainer." << std::endl;
                }
                break;
            }
            case 5: {
                int trainerId;
                double score;
                std::string review;
                std::cout << "Enter Trainer ID to rate: "; std::cin >> trainerId;
                std::cout << "Enter Rating Score (1.0 to 5.0): "; std::cin >> score;
                std::cout << "Enter short review text: "; 
                std::cin.ignore();
                std::getline(std::cin, review);

                if(memberService->rateTrainer(currentUserId, trainerId, score, review)) {
                    std::cout << "Rating submitted successfully!" << std::endl;
                } else {
                    std::cout << "Failed to submit rating." << std::endl;
                }
                break;
            }
            case 6: {
                double bmi = memberService->calculateBMI(currentUserId);
                if (bmi > 0.0) {
                    std::cout << "Your BMI is: " << bmi << std::endl;
                    if (bmi < 18.5) std::cout << "Category: Underweight" << std::endl;
                    else if (bmi < 24.9) std::cout << "Category: Normal weight" << std::endl;
                    else if (bmi < 29.9) std::cout << "Category: Overweight" << std::endl;
                    else std::cout << "Category: Obese" << std::endl;
                } else {
                    std::cout << "Height or Weight data not available for your profile. Please ask admin to update." << std::endl;
                }
                break;
            }
            case 7:
                authService->logout();
                std::cout << "Logged out successfully." << std::endl;
                return;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}
