#include <iostream>
#include <memory>
#include "include/DatabaseManager.h"
#include "include/AuthModule.h"
#include "include/MemberModule.h"
#include "include/HealthModule.h"

int main() {
    auto db = std::make_shared<DatabaseManager>();
    
    if (!db->openDatabase("gym_management.db")) {
        std::cerr << "Failed to open database!" << std::endl;
        return 1;
    }
    
    AuthModule auth(*db);
    MemberModule members(*db);
    HealthModule health(*db);
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "  GYM MANAGEMENT SYSTEM - SETUP" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    // Create sample trainers
    std::cout << "[1/3] Creating sample trainers..." << std::endl;
    auth.registerUser("sarah_trainer", "trainer123", TRAINER);
    auth.registerUser("mike_trainer", "trainer456", TRAINER);
    auth.registerUser("alex_trainer", "trainer789", TRAINER);
    std::cout << "✓ 3 trainers created\n" << std::endl;
    
    // Create sample admin
    std::cout << "[2/3] Creating sample admin..." << std::endl;
    auth.registerUser("admin_user", "admin123", ADMIN);
    std::cout << "✓ 1 admin created\n" << std::endl;
    
    // Create 10 sample members with health data
    std::cout << "[3/3] Creating 10 sample members..." << std::endl;
    
    struct SampleMember {
        std::string name;
        int age;
        std::string gender;
        double height;
        double weight;
        std::string membership;
    };
    
    SampleMember sampleMembers[] = {
        {"John Doe", 25, "Male", 175, 75, "Gold"},
        {"Sarah Johnson", 28, "Female", 162, 58, "Gold"},
        {"Michael Brown", 35, "Male", 180, 85, "Silver"},
        {"Emily Davis", 22, "Female", 168, 62, "Gold"},
        {"David Wilson", 45, "Male", 178, 92, "Bronze"},
        {"Jessica Martinez", 30, "Female", 165, 70, "Silver"},
        {"James Anderson", 32, "Male", 182, 88, "Gold"},
        {"Amanda Taylor", 26, "Female", 160, 55, "Gold"},
        {"Christopher Lee", 40, "Male", 176, 95, "Silver"},
        {"Nicole White", 29, "Female", 170, 65, "Gold"}
    };
    
    for (const auto& member : sampleMembers) {
        if (members.addMember(member.name, member.age, member.gender, 
                             member.height, member.weight, member.membership)) {
            
            // Get the member ID (assuming it's sequential or we need to search)
            std::vector<Member> searchResults;
            if (members.searchMemberByName(member.name, searchResults)) {
                for (const auto& found : searchResults) {
                    if (found.name == member.name) {
                        // Record initial health data
                        health.recordHealth(found.id, member.height, member.weight);
                        break;
                    }
                }
            }
        }
    }
    
    std::cout << "✓ 10 members created with health records\n" << std::endl;
    
    std::cout << "========================================" << std::endl;
    std::cout << "  SETUP COMPLETE!" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    std::cout << "Sample Accounts Created:\n" << std::endl;
    std::cout << "TRAINERS:" << std::endl;
    std::cout << "  Username: sarah_trainer  | Password: trainer123  | Role: Trainer" << std::endl;
    std::cout << "  Username: mike_trainer   | Password: trainer456  | Role: Trainer" << std::endl;
    std::cout << "  Username: alex_trainer   | Password: trainer789  | Role: Trainer" << std::endl;
    
    std::cout << "\nADMIN:" << std::endl;
    std::cout << "  Username: admin_user     | Password: admin123    | Role: Admin" << std::endl;
    
    std::cout << "\nMEMBERS (10 sample members with data):" << std::endl;
    std::cout << "  1. John Doe (25, Male, Gold)" << std::endl;
    std::cout << "  2. Sarah Johnson (28, Female, Gold)" << std::endl;
    std::cout << "  3. Michael Brown (35, Male, Silver)" << std::endl;
    std::cout << "  4. Emily Davis (22, Female, Gold)" << std::endl;
    std::cout << "  5. David Wilson (45, Male, Bronze)" << std::endl;
    std::cout << "  6. Jessica Martinez (30, Female, Silver)" << std::endl;
    std::cout << "  7. James Anderson (32, Male, Gold)" << std::endl;
    std::cout << "  8. Amanda Taylor (26, Female, Gold)" << std::endl;
    std::cout << "  9. Christopher Lee (40, Male, Silver)" << std::endl;
    std::cout << "  10. Nicole White (29, Female, Gold)" << std::endl;
    
    std::cout << "\nYou can now login to GymApp.exe with any of these accounts!" << std::endl;
    std::cout << "\nPress Enter to exit...";
    std::cin.ignore();
    std::cin.ignore();
    
    return 0;
}
