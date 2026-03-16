#include "../../../include/Application/Services/AdminService.h"
#include "../../../include/Domain/Entities/Member.h"
#include "../../../include/Domain/Entities/Trainer.h"
#include "../../../include/Infrastructure/Repositories/WorkoutRepository.h"
#include "../../../include/Infrastructure/Repositories/ProgressRepository.h"
#include <iostream>

bool AdminService::addMember(const std::string& name, const std::string& email, const std::string& phone, const std::string& password, int age, double height, double weight, const std::string& membershipType) {
    std::unique_ptr<User> user = std::make_unique<Member>(0, name, email, phone, password, 0, age, weight, height, membershipType, 0); // initial dummy IDs
    if (userRepo.add(user)) {
        Member newMember;
        newMember.setUserId(user->getUserId());
        newMember.setAge(age);
        newMember.setHeight(height);
        newMember.setWeight(weight);
        newMember.setMembershipType(membershipType);
        newMember.setTrainerId(0);
        return memberRepo.add(newMember);
    }
    return false;
}

bool AdminService::removeMember(int memberId) {
    auto member = memberRepo.getById(memberId);
    if(member.getMemberId() == 0) return false;
    
    // Remove from Member table
    bool memRemoved = memberRepo.remove(memberId);
    // Remove from User table
    bool userRemoved = userRepo.remove(member.getUserId());
    
    return memRemoved && userRemoved;
}

bool AdminService::addTrainer(const std::string& name, const std::string& email, const std::string& phone, const std::string& password, const std::string& specialization, int experienceYears) {
    std::unique_ptr<User> user = std::make_unique<Trainer>(0, name, email, phone, password, 0, specialization, experienceYears, 0.0);
    if (userRepo.add(user)) {
        Trainer newTrainer;
        newTrainer.setUserId(user->getUserId());
        newTrainer.setSpecialization(specialization);
        newTrainer.setExperienceYears(experienceYears);
        newTrainer.setRating(0.0);
        return trainerRepo.add(newTrainer);
    }
    return false;
}

bool AdminService::removeTrainer(int trainerId) {
    auto trainer = trainerRepo.getById(trainerId);
    if(trainer.getTrainerId() == 0) return false;
    
    bool trainerRemoved = trainerRepo.remove(trainerId);
    bool userRemoved = userRepo.remove(trainer.getUserId());
    
    // Unassign members
    auto assignedMembers = memberRepo.getByTrainerId(trainerId);
    for(auto& m : assignedMembers) {
        m.setTrainerId(0);
        memberRepo.update(m);
    }
    
    return trainerRemoved && userRemoved;
}

bool AdminService::assignTrainerToMember(int memberId, int trainerId) {
    auto member = memberRepo.getById(memberId);
    if(member.getMemberId() == 0) return false;
    
    member.setTrainerId(trainerId);
    return memberRepo.update(member);
}

std::vector<Member> AdminService::viewAllMembers() {
    return memberRepo.getAll();
}

std::vector<Trainer> AdminService::viewAllTrainers() {
    return trainerRepo.getAll();
}

void AdminService::generateReports() {
    std::cout << "\n=== SYSTEM REPORT ===" << std::endl;
    auto members = viewAllMembers();
    auto trainers = viewAllTrainers();
    
    std::cout << "Total Members registered: " << members.size() << std::endl;
    std::cout << "Total Trainers registered: " << trainers.size() << std::endl;
    std::cout << "=====================" << std::endl;
}

// System Test Functions as required
void AdminService::testDatabaseConnection() {
    DatabaseManager* db = DatabaseManager::getInstance();
    if(db->getDatabase() != nullptr) {
        std::cout << "[TEST PASSED] Database connection successful." << std::endl;
    } else {
        std::cout << "[TEST FAILED] Database is not connected." << std::endl;
    }
}

void AdminService::testUserCreation() {
    std::cout << "Testing user creation..." << std::endl;
    bool success = addTrainer("Test Trainer", "test@trainer.com", "555-0000", "pass123", "Yoga", 5);
    if(success) {
        std::cout << "[TEST PASSED] Trainer 'Test Trainer' created successfully." << std::endl;
    } else {
        std::cout << "[TEST FAILED] Trainer creation failed." << std::endl;
    }
}

void AdminService::testTrainerAssignment() {
    std::cout << "Testing trainer assignment..." << std::endl;
    // Assuming we have records, we take the first member and first trainer
    auto members = memberRepo.getAll();
    auto trainers = trainerRepo.getAll();
    if(!members.empty() && !trainers.empty()) {
        bool success = assignTrainerToMember(members[0].getMemberId(), trainers[0].getTrainerId());
        if(success) {
            std::cout << "[TEST PASSED] Assigned Trainer ID " << trainers[0].getTrainerId() << " to Member ID " << members[0].getMemberId() << " successfully." << std::endl;
        } else {
            std::cout << "[TEST FAILED] Trainer assignment failed." << std::endl;
        }
    } else {
        std::cout << "[TEST SKIPPED] Not enough data to test assignment." << std::endl;
    }
}

void AdminService::testWorkoutPlanCreation() {
    std::cout << "Testing workout plan creation..." << std::endl;
    auto members = memberRepo.getAll();
    auto trainers = trainerRepo.getAll();
    if(!members.empty() && !trainers.empty()) {
        WorkoutRepository wr;
        WorkoutPlan plan(0, members[0].getMemberId(), trainers[0].getTrainerId(), "Pushups, Situps", 4, "Intermediate");
        bool success = wr.add(plan);
        if(success) {
            std::cout << "[TEST PASSED] Workout plan created successfully." << std::endl;
        } else {
            std::cout << "[TEST FAILED] Workout plan creation failed." << std::endl;
        }
    } else {
        std::cout << "[TEST SKIPPED] Not enough data to test workout plan creation." << std::endl;
    }
}

void AdminService::testProgressTracking() {
    std::cout << "Testing progress tracking..." << std::endl;
    auto members = memberRepo.getAll();
    if(!members.empty()) {
        ProgressRepository pr;
        HealthProgress hp(0, members[0].getMemberId(), 75.5, 15.2, 40.1, "2026-03-12");
        bool success = pr.add(hp);
        if(success) {
            std::cout << "[TEST PASSED] Health progress tracked successfully." << std::endl;
        } else {
            std::cout << "[TEST FAILED] Health progress tracking failed." << std::endl;
        }
    } else {
        std::cout << "[TEST SKIPPED] Not enough data to test progress tracking." << std::endl;
    }
}
