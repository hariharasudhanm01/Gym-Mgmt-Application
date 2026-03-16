#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <iostream>

class Member : public User {
private:
    int memberId;
    int age;
    double weight;
    double height;
    std::string membershipType;
    int trainerId;

public:
    Member() : User(), memberId(0), age(0), weight(0.0), height(0.0), trainerId(0) {
        this->role = Role::Member;
    }
    
    Member(int uId, const std::string& n, const std::string& e, const std::string& p, const std::string& pwd,
           int mId, int a, double w, double h, const std::string& memType, int tId)
        : User(uId, n, e, p, pwd, Role::Member), memberId(mId), age(a), weight(w), height(h),
          membershipType(memType), trainerId(tId) {}
          
    int getMemberId() const { return memberId; }
    void setMemberId(int id) { memberId = id; }
    
    int getAge() const { return age; }
    void setAge(int a) { age = a; }
    
    double getWeight() const { return weight; }
    void setWeight(double w) { weight = w; }
    
    double getHeight() const { return height; }
    void setHeight(double h) { height = h; }
    
    std::string getMembershipType() const { return membershipType; }
    void setMembershipType(const std::string& t) { membershipType = t; }
    
    int getTrainerId() const { return trainerId; }
    void setTrainerId(int id) { trainerId = id; }

    // User overrides
    void login() override {
        std::cout << "Member " << name << " logged in." << std::endl;
    }
    
    void logout() override {
        std::cout << "Member " << name << " logged out." << std::endl;
    }

    // Domain Specific Methods are implemented in the Service layer
    // such as viewHealthProgress(), viewWorkoutPlan(), rateTrainer()
};

#endif
