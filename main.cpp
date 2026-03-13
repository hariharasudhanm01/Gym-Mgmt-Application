#include <iostream>
#include <memory>
#include <iomanip>
#include "include/DatabaseManager.h"
#include "include/AuthModule.h"
#include "include/MemberModule.h"
#include "include/HealthModule.h"
#include "include/StatisticsModule.h"
#include "include/WorkoutModule.h"
#include "include/ProgressModule.h"

// ==================== Function Declarations ====================
void displayMainMenu();
void displayMemberDashboard(std::shared_ptr<DatabaseManager> db, AuthModule& auth);
void displayTrainerMenu(std::shared_ptr<DatabaseManager> db, AuthModule& auth, MemberModule& members);
void displayAdminMenu(std::shared_ptr<DatabaseManager> db, AuthModule& auth);
void displayMemberHealthHistory(MemberModule& members, HealthModule& health);
void populateSampleData(std::shared_ptr<DatabaseManager> db, MemberModule& members, 
                        HealthModule& health, WorkoutModule& workout, ProgressModule& progress);

int main() {
    auto db = std::make_shared<DatabaseManager>();
    
    // Open database connection
    if (!db->openDatabase("gym_management.db")) {
        std::cerr << "Failed to open database!" << std::endl;
        return 1;
    }
    
    // Initialize all modules
    AuthModule auth(*db);
    MemberModule members(*db);
    HealthModule health(*db);
    StatisticsModule stats(*db);
    WorkoutModule workout(*db);
    ProgressModule progress(*db);
    
    // Main application loop
    int mainChoice;
    while (true) {
        displayMainMenu();
        std::cin >> mainChoice;
        
        switch (mainChoice) {
            case 1:
                // Register new user
                auth.displayRegistrationMenu();
                break;
            case 2:
                // Login
                auth.displayLoginMenu();
                if (auth.isLoggedIn()) {
                    UserRole role = auth.getCurrentRole();
                    
                    if (role == MEMBER) {
                        displayMemberDashboard(db, auth);
                    } else if (role == TRAINER) {
                        displayTrainerMenu(db, auth, members);
                    } else if (role == ADMIN) {
                        displayAdminMenu(db, auth);
                    }
                }
                break;
            case 3:
                // Exit application
                std::cout << "Thank you for using Gym Management System!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
    
    return 0;
}

// ==================== Menu Display Functions ====================

void displayMainMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "   GYM MANAGEMENT SYSTEM - MAIN MENU" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "\n1. Register New User" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "\nChoose an option: ";
}

// Display member dashboard and handle member menu options
void displayMemberDashboard(std::shared_ptr<DatabaseManager> db, AuthModule& auth) {
    HealthModule health(*db);
    ProgressModule progress(*db);
    WorkoutModule workout(*db);
    
    std::cout << "\n=== MEMBER DASHBOARD ===" << std::endl;
    std::cout << "Welcome, " << auth.getCurrentUsername() << std::endl;
    
    int memberChoice;
    while (true) {
        std::cout << "\n1. View My Health Data" << std::endl;
        std::cout << "2. View My Health Insights" << std::endl;
        std::cout << "3. View My Progress" << std::endl;
        std::cout << "4. View My Workout Plans" << std::endl;
        std::cout << "5. Logout" << std::endl;
        std::cout << "Choice: ";
        std::cin >> memberChoice;

        switch (memberChoice) {
            case 1:
                health.displayHealthMenu();
                break;
            case 2:
                health.displayHealthInsights(auth.getCurrentUserId());
                break;
            case 3:
                progress.displayProgressMenu();
                break;
            case 4: {
                // View workout plans
                std::vector<WorkoutPlan> plans;
                if (workout.getMemberWorkoutPlans(auth.getCurrentUserId(), plans)) {
                    std::cout << "\n=== YOUR WORKOUT PLANS ===" << std::endl;
                    for (const auto& plan : plans) {
                        std::cout << "- " << plan.planName << " (" << plan.difficulty << ")" << std::endl;
                    }
                } else {
                    std::cout << "No workout plans assigned yet." << std::endl;
                }
                break;
            }
            case 5:
                auth.logout();
                return;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
}

// Display trainer dashboard and handle trainer menu options
void displayTrainerMenu(std::shared_ptr<DatabaseManager> db, AuthModule& auth, MemberModule& members) {
    HealthModule health(*db);
    StatisticsModule stats(*db);
    WorkoutModule workout(*db);
    ProgressModule progress(*db);
    
    std::cout << "\n=== TRAINER DASHBOARD ===" << std::endl;
    std::cout << "Welcome, " << auth.getCurrentUsername() << std::endl;
    
    int trainerChoice;
    while (true) {
        std::cout << "\n1. Manage Members" << std::endl;
        std::cout << "2. Record Health Data" << std::endl;
        std::cout << "3. Create Workout Plans" << std::endl;
        std::cout << "4. View Member Progress" << std::endl;
        std::cout << "5. View Gym Statistics" << std::endl;
        std::cout << "6. Logout" << std::endl;
        std::cout << "Choice: ";
        std::cin >> trainerChoice;
        
        switch (trainerChoice) {
            case 1:
                members.displayMemberMenu();
                break;
            case 2:
                health.displayHealthMenu();
                break;
            case 3:
                workout.displayWorkoutMenu();
                break;
            case 4:
                progress.displayProgressMenu();
                break;
            case 5:
                stats.displayStatistics();
                stats.displayMemberDistribution();
                stats.displayBMIDistribution();
                break;
            case 6:
                auth.logout();
                return;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
}

// Display admin member health history - extracted for readability
void displayMemberHealthHistory(MemberModule& members, HealthModule& health) {
    std::vector<Member> allMembers;
    
    if (!members.getAllMembers(allMembers) || allMembers.empty()) {
        std::cout << "No members found." << std::endl;
        return;
    }
    
    std::cout << "\n=== MEMBER LIST ===" << std::endl;
    for (const auto& m : allMembers) {
        std::cout << "ID: " << m.id << " | Name: " << m.name << std::endl;
    }
    
    int memberId;
    std::cout << "\nEnter Member ID to view health history: ";
    std::cin >> memberId;
    
    std::vector<HealthRecord> records;
    if (health.getAllHealthRecords(memberId, records) && !records.empty()) {
        std::cout << "\n=== HEALTH HISTORY FOR MEMBER ID " << memberId << " ===" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        std::cout << "Date | Height | Weight | BMI | Category" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        
        for (const auto& record : records) {
            std::cout << record.recordDate << " | " << record.height
                      << " | " << record.weight << " | "
                      << std::fixed << std::setprecision(2) << record.bmi
                      << " | " << record.category << std::endl;
        }
    } else {
        std::cout << "No health records found for this member." << std::endl;
    }
}

// Display admin dashboard and handle admin menu options
void displayAdminMenu(std::shared_ptr<DatabaseManager> db, AuthModule& auth) {
    MemberModule members(*db);
    HealthModule health(*db);
    StatisticsModule stats(*db);
    WorkoutModule workout(*db);
    ProgressModule progress(*db);
    
    std::cout << "\n=== ADMIN DASHBOARD ===" << std::endl;
    std::cout << "Welcome, " << auth.getCurrentUsername() << std::endl;
    
    int adminChoice;
    while (true) {
        std::cout << "\n1. Member Management" << std::endl;
        std::cout << "2. Health Management" << std::endl;
        std::cout << "3. Workout Management" << std::endl;
        std::cout << "4. Progress Tracking" << std::endl;
        std::cout << "5. View Statistics" << std::endl;
        std::cout << "6. View Health History of Member" << std::endl;
        std::cout << "7. Populate Sample Data (for testing)" << std::endl;
        std::cout << "8. Logout" << std::endl;
        std::cout << "\nChoice: ";
        std::cin >> adminChoice;

        switch (adminChoice) {
            case 1:
                members.displayMemberMenu();
                break;
            case 2:
                health.displayHealthMenu();
                break;
            case 3:
                workout.displayWorkoutMenu();
                break;
            case 4:
                progress.displayProgressMenu();
                break;
            case 5:
                stats.displayStatistics();
                stats.displayMemberDistribution();
                stats.displayBMIDistribution();
                break;
            case 6:
                displayMemberHealthHistory(members, health);
                break;
            case 7:
                populateSampleData(db, members, health, workout, progress);
                break;
            case 8:
                auth.logout();
                return;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
}

// ==================== Sample Data Population ====================

// Populate database with sample data for testing and demonstration
void populateSampleData(std::shared_ptr<DatabaseManager> db, MemberModule& members, 
                        HealthModule& health, WorkoutModule& workout, ProgressModule& progress) {
    std::cout << "\n=== POPULATING SAMPLE DATA ===" << std::endl;
    
    // Get all existing members
    std::vector<Member> allMembers;
    if (!members.getAllMembers(allMembers) || allMembers.empty()) {
        std::cout << "No members found. Please add members first." << std::endl;
        return;
    }
    
    std::cout << "Found " << allMembers.size() << " member(s). Adding sample data..." << std::endl;
    
    // Add sample health records for each member
    for (const auto& member : allMembers) {
        std::cout << "\nAdding data for: " << member.name << "..." << std::endl;
        
        // Add initial health record (2 months ago)
        health.recordHealth(member.id, member.height, member.weight + 5.0);
        
        // Add progress record (1 month ago)
        progress.recordProgress(member.id, member.weight + 2.5, "Improved cardio endurance");
        
        // Add another health record (1 week ago)
        health.recordHealth(member.id, member.height, member.weight + 1.0);
        
        // Add progress record (current)
        progress.recordProgress(member.id, member.weight, "Consistent workout routine - 3x per week");
        
        // Add another health record (today)
        health.recordHealth(member.id, member.height, member.weight);
        
        std::cout << "  ✓ Added 3 health records";
        std::cout << "\n  ✓ Added 2 progress achievements";
    }
    
    // Add sample workout plans for each member
    for (const auto& member : allMembers) {
        std::string planNames[] = {"Beginner Full Body", "Intermediate Strength", "Advanced HIIT"};
        std::string difficulties[] = {"Easy", "Medium", "Hard"};
        
        int planCount = 0;
        for (int i = 0; i < 2; i++) {
            if (workout.createWorkoutPlan(member.id, planNames[i], difficulties[i])) {
                planCount++;
            }
        }
        std::cout << "\n  ✓ Added " << planCount << " workout plans for " << member.name;
    }
    
    std::cout << "\n\n=== SAMPLE DATA POPULATION COMPLETE ===" << std::endl;
    std::cout << "Sample data has been added successfully!" << std::endl;
    std::cout << "You can now login and view the sample data in your dashboards." << std::endl;
}