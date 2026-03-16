#ifndef ADMIN_SERVICE_H
#define ADMIN_SERVICE_H

#include "../../Infrastructure/Repositories/MemberRepository.h"
#include "../../Infrastructure/Repositories/TrainerRepository.h"
#include "../../Infrastructure/Repositories/UserRepository.h"
#include "../../Infrastructure/Database/DatabaseManager.h"
#include <vector>
#include <memory>

class AdminService {
private:
    UserRepository userRepo;
    MemberRepository memberRepo;
    TrainerRepository trainerRepo;

public:
    AdminService() = default;

    // Administrative Functions
    bool addMember(const std::string& name, const std::string& email, const std::string& phone, const std::string& password, int age, double height, double weight, const std::string& membershipType);
    bool removeMember(int memberId);
    bool addTrainer(const std::string& name, const std::string& email, const std::string& phone, const std::string& password, const std::string& specialization, int experienceYears);
    bool removeTrainer(int trainerId);
    bool assignTrainerToMember(int memberId, int trainerId);
    std::vector<Member> viewAllMembers();
    std::vector<Trainer> viewAllTrainers();
    void generateReports();

    // System Test Functions
    void testDatabaseConnection();
    void testUserCreation();
    void testTrainerAssignment();
    void testWorkoutPlanCreation();
    void testProgressTracking();
};

#endif
