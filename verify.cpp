#include <iostream>
#include <memory>
#include "include/DatabaseManager.h"
#include "include/MemberModule.h"

int main() {
    auto db = std::make_shared<DatabaseManager>();
    
    if (!db->openDatabase("gym_management.db")) {
        std::cerr << "Database not found!" << std::endl;
        return 1;
    }
    
    MemberModule members(*db);
    std::vector<Member> allMembers;
    
    if (members.getAllMembers(allMembers)) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  SAMPLE DATA VERIFICATION" << std::endl;
        std::cout << "========================================\n" << std::endl;
        
        std::cout << "Total Members: " << allMembers.size() << std::endl;
        std::cout << "\nMember List:\n" << std::endl;
        
        for (size_t i = 0; i < allMembers.size(); i++) {
            const auto& m = allMembers[i];
            std::cout << (i+1) << ". " << m.name << " (ID: " << m.id << ")" << std::endl;
            std::cout << "   Age: " << m.age << " | Gender: " << m.gender << std::endl;
            std::cout << "   Height: " << m.height << "cm | Weight: " << m.weight << "kg" << std::endl;
            std::cout << "   Membership: " << m.membershipType << " | Expires: " << m.expiryDate << std::endl;
            std::cout << std::endl;
        }
        
        std::cout << "========================================\n" << std::endl;
        std::cout << "Setup Complete! You can now login to GymApp.exe\n" << std::endl;
        std::cout << "Test Accounts:\n" << std::endl;
        std::cout << "ADMIN:" << std::endl;
        std::cout << "  Username: admin_user  | Password: admin123\n" << std::endl;
        std::cout << "TRAINERS:" << std::endl;
        std::cout << "  Username: sarah_trainer | Password: trainer123" << std::endl;
        std::cout << "  Username: mike_trainer  | Password: trainer456" << std::endl;
        std::cout << "  Username: alex_trainer  | Password: trainer789" << std::endl;
        
    } else {
        std::cout << "Failed to retrieve members!" << std::endl;
    }
    
    return 0;
}
