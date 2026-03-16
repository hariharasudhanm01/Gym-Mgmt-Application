#ifndef TRAINER_ENTITY_H
#define TRAINER_ENTITY_H

#include "User.h"
#include <vector>
#include <iostream>

class Trainer : public User {
private:
    int trainerId;
    std::string specialization;
    int experienceYears;
    double rating;
    std::vector<int> assignedMemberIds;

public:
    Trainer() : User(), trainerId(0), experienceYears(0), rating(0.0) {
        this->role = Role::Trainer;
    }
    
    Trainer(int uId, const std::string& n, const std::string& e, const std::string& p, const std::string& pwd,
            int tId, const std::string& spec, int expYears, double rat)
        : User(uId, n, e, p, pwd, Role::Trainer), trainerId(tId), specialization(spec),
          experienceYears(expYears), rating(rat) {}

    int getTrainerId() const { return trainerId; }
    void setTrainerId(int id) { trainerId = id; }
    
    std::string getSpecialization() const { return specialization; }
    void setSpecialization(const std::string& spec) { specialization = spec; }
    
    int getExperienceYears() const { return experienceYears; }
    void setExperienceYears(int years) { experienceYears = years; }
    
    double getRating() const { return rating; }
    void setRating(double r) { rating = r; }
    
    std::vector<int> getAssignedMembers() const { return assignedMemberIds; }
    void addAssignedMember(int memberId) { assignedMemberIds.push_back(memberId); }

    void login() override {
        std::cout << "Trainer " << name << " logged in." << std::endl;
    }
    
    void logout() override {
        std::cout << "Trainer " << name << " logged out." << std::endl;
    }
};

#endif
