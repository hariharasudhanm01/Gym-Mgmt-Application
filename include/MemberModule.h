#ifndef MEMBER_MODULE_H
#define MEMBER_MODULE_H

#include <string>
#include <vector>
#include "DatabaseManager.h"

struct Member {
    int id;
    std::string name;
    int age;
    std::string gender;
    double height;
    double weight;
    std::string membershipType; // Gold, Silver, Bronze
    std::string joinDate;
    std::string expiryDate;
};

class MemberModule {
private:
    DatabaseManager& db;
    
public:
    MemberModule(DatabaseManager& database);
    
    bool addMember(const std::string& name, int age, const std::string& gender,
                   double height, double weight, const std::string& membershipType);
    bool updateMember(int memberId, const std::string& name, int age,
                      const std::string& gender, double height, double weight,
                      const std::string& membershipType);
    bool deleteMember(int memberId);
    bool getMember(int memberId, Member& member);
    bool getAllMembers(std::vector<Member>& members);
    bool searchMemberByName(const std::string& name, std::vector<Member>& members);
    void displayMemberMenu();
    
private:
    std::string getCurrentDate();
    std::string getExpiryDate(const std::string& membershipType);
};

#endif
