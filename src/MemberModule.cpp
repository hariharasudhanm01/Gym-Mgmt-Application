#include "../include/MemberModule.h"
#include "../libs/sqlite/sqlite3.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

MemberModule::MemberModule(DatabaseManager& database) : db(database) {}

std::string MemberModule::getCurrentDate() {
    time_t now = time(0);
    std::tm* timeinfo = localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d");
    return oss.str();
}

std::string MemberModule::getExpiryDate(const std::string& membershipType) {
    time_t now = time(0);
    std::tm* timeinfo = localtime(&now);
    
    // Different expiry based on membership type
    int months = 0;
    if (membershipType == "Gold") months = 12;
    else if (membershipType == "Silver") months = 6;
    else if (membershipType == "Bronze") months = 3;
    
    timeinfo->tm_mon += months;
    if (timeinfo->tm_mon > 11) {
        timeinfo->tm_mon -= 12;
        timeinfo->tm_year += 1;
    }
    
    time_t expiry = mktime(timeinfo);
    std::tm* expiryInfo = localtime(&expiry);
    
    std::ostringstream oss;
    oss << std::put_time(expiryInfo, "%Y-%m-%d");
    return oss.str();
}

bool MemberModule::addMember(const std::string& name, int age, const std::string& gender,
                              double height, double weight, const std::string& membershipType) {
    std::string joinDate = getCurrentDate();
    std::string expiryDate = getExpiryDate(membershipType);
    
    std::ostringstream query;
    query << "INSERT INTO members (name, age, gender, height, weight, membershipType, joinDate, expiryDate) "
          << "VALUES ('" << name << "', " << age << ", '" << gender << "', " << height 
          << ", " << weight << ", '" << membershipType << "', '" << joinDate << "', '" 
          << expiryDate << "');";
    
    if (!db.executeQuery(query.str())) {
        std::cout << "Error adding member." << std::endl;
        return false;
    }
    
    std::cout << "Member added successfully!" << std::endl;
    return true;
}

bool MemberModule::updateMember(int memberId, const std::string& name, int age,
                                 const std::string& gender, double height, double weight,
                                 const std::string& membershipType) {
    std::ostringstream query;
    query << "UPDATE members SET name = '" << name << "', age = " << age 
          << ", gender = '" << gender << "', height = " << height 
          << ", weight = " << weight << ", membershipType = '" << membershipType 
          << "' WHERE id = " << memberId << ";";
    
    if (!db.executeQuery(query.str())) {
        std::cout << "Error updating member." << std::endl;
        return false;
    }
    
    std::cout << "Member updated successfully!" << std::endl;
    return true;
}

bool MemberModule::deleteMember(int memberId) {
    std::ostringstream query;
    query << "UPDATE members SET active = 0 WHERE id = " << memberId << ";";
    
    if (!db.executeQuery(query.str())) {
        std::cout << "Error deleting member." << std::endl;
        return false;
    }
    
    std::cout << "Member deleted successfully!" << std::endl;
    return true;
}

bool MemberModule::getMember(int memberId, Member& member) {
    std::ostringstream query;
    query << "SELECT id, name, age, gender, height, weight, membershipType, joinDate, expiryDate "
          << "FROM members WHERE id = " << memberId << " AND active = 1;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query.str());
    if (!stmt) return false;
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        member.id = sqlite3_column_int(stmt, 0);
        member.name = (char*)sqlite3_column_text(stmt, 1);
        member.age = sqlite3_column_int(stmt, 2);
        member.gender = (char*)sqlite3_column_text(stmt, 3);
        member.height = sqlite3_column_double(stmt, 4);
        member.weight = sqlite3_column_double(stmt, 5);
        member.membershipType = (char*)sqlite3_column_text(stmt, 6);
        member.joinDate = (char*)sqlite3_column_text(stmt, 7);
        member.expiryDate = (char*)sqlite3_column_text(stmt, 8);
        
        db.finalizeStatement(stmt);
        return true;
    }
    
    db.finalizeStatement(stmt);
    return false;
}

bool MemberModule::getAllMembers(std::vector<Member>& members) {
    const char* query = "SELECT id, name, age, gender, height, weight, membershipType, joinDate, expiryDate "
                        "FROM members WHERE active = 1 ORDER BY name;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query);
    if (!stmt) return false;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Member member;
        member.id = sqlite3_column_int(stmt, 0);
        member.name = (char*)sqlite3_column_text(stmt, 1);
        member.age = sqlite3_column_int(stmt, 2);
        member.gender = (char*)sqlite3_column_text(stmt, 3);
        member.height = sqlite3_column_double(stmt, 4);
        member.weight = sqlite3_column_double(stmt, 5);
        member.membershipType = (char*)sqlite3_column_text(stmt, 6);
        member.joinDate = (char*)sqlite3_column_text(stmt, 7);
        member.expiryDate = (char*)sqlite3_column_text(stmt, 8);
        
        members.push_back(member);
    }
    
    db.finalizeStatement(stmt);
    return true;
}

bool MemberModule::searchMemberByName(const std::string& name, std::vector<Member>& members) {
    std::ostringstream query;
    query << "SELECT id, name, age, gender, height, weight, membershipType, joinDate, expiryDate "
          << "FROM members WHERE name LIKE '%" << name << "%' AND active = 1 ORDER BY name;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query.str());
    if (!stmt) return false;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Member member;
        member.id = sqlite3_column_int(stmt, 0);
        member.name = (char*)sqlite3_column_text(stmt, 1);
        member.age = sqlite3_column_int(stmt, 2);
        member.gender = (char*)sqlite3_column_text(stmt, 3);
        member.height = sqlite3_column_double(stmt, 4);
        member.weight = sqlite3_column_double(stmt, 5);
        member.membershipType = (char*)sqlite3_column_text(stmt, 6);
        member.joinDate = (char*)sqlite3_column_text(stmt, 7);
        member.expiryDate = (char*)sqlite3_column_text(stmt, 8);
        
        members.push_back(member);
    }
    
    db.finalizeStatement(stmt);
    return true;
}

void MemberModule::displayMemberMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n=== MEMBER MANAGEMENT ===" << std::endl;
        std::cout << "1. Add New Member" << std::endl;
        std::cout << "2. View All Members" << std::endl;
        std::cout << "3. Search Member by Name" << std::endl;
        std::cout << "4. Update Member" << std::endl;
        std::cout << "5. Delete Member" << std::endl;
        std::cout << "6. Back to Main Menu" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        
        if (choice == 1) {
            // Add member
            std::string name, gender, membershipType;
            int age;
            double height, weight;
            
            std::cout << "Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Age: ";
            std::cin >> age;
            std::cout << "Gender: ";
            std::cin >> gender;
            std::cout << "Height (cm): ";
            std::cin >> height;
            std::cout << "Weight (kg): ";
            std::cin >> weight;
            std::cout << "Membership Type (Gold/Silver/Bronze): ";
            std::cin >> membershipType;
            
            addMember(name, age, gender, height, weight, membershipType);
        }
        else if (choice == 2) {
            std::vector<Member> members;
            if (getAllMembers(members)) {
                std::cout << "\n=== ALL MEMBERS ===" << std::endl;
                std::cout << std::string(100, '-') << std::endl;
                std::cout << "ID | Name | Age | Gender | Height | Weight | Membership | Expiry" << std::endl;
                std::cout << std::string(100, '-') << std::endl;
                
                for (const auto& member : members) {
                    std::cout << member.id << " | " << member.name << " | " << member.age 
                              << " | " << member.gender << " | " << member.height 
                              << " | " << member.weight << " | " << member.membershipType 
                              << " | " << member.expiryDate << std::endl;
                }
            }
        }
        else if (choice == 3) {
            std::string name;
            std::cout << "Search by name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            
            std::vector<Member> members;
            if (searchMemberByName(name, members)) {
                std::cout << "\n=== SEARCH RESULTS ===" << std::endl;
                for (const auto& member : members) {
                    std::cout << "ID: " << member.id << ", Name: " << member.name 
                              << ", Age: " << member.age << std::endl;
                }
            }
        }
        else if (choice == 4) {
            // Update member
            int memberId;
            std::cout << "Enter Member ID to update: ";
            std::cin >> memberId;
            
            Member member;
            if (getMember(memberId, member)) {
                std::cout << "\n=== Current Member Info ===" << std::endl;
                std::cout << "Name: " << member.name << std::endl;
                std::cout << "Age: " << member.age << std::endl;
                std::cout << "Gender: " << member.gender << std::endl;
                std::cout << "Height: " << member.height << " cm" << std::endl;
                std::cout << "Weight: " << member.weight << " kg" << std::endl;
                std::cout << "Membership: " << member.membershipType << std::endl;
                
                std::cout << "\n=== Enter New Information ===" << std::endl;
                std::string name, gender, membershipType;
                int age;
                double height, weight;
                
                std::cout << "Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Age: ";
                std::cin >> age;
                std::cout << "Gender: ";
                std::cin >> gender;
                std::cout << "Height (cm): ";
                std::cin >> height;
                std::cout << "Weight (kg): ";
                std::cin >> weight;
                std::cout << "Membership Type (Gold/Silver/Bronze): ";
                std::cin >> membershipType;
                
                if (updateMember(memberId, name, age, gender, height, weight, membershipType)) {
                    std::cout << "Member updated successfully!" << std::endl;
                } else {
                    std::cout << "Failed to update member." << std::endl;
                }
            } else {
                std::cout << "Member not found!" << std::endl;
            }
        }
        else if (choice == 5) {
            // Delete member
            int memberId;
            std::cout << "Enter Member ID to delete: ";
            std::cin >> memberId;
            
            Member member;
            if (getMember(memberId, member)) {
                std::cout << "\nMember: " << member.name << std::endl;
                std::cout << "Are you sure you want to delete? (y/n): ";
                char confirm;
                std::cin >> confirm;
                
                if (confirm == 'y' || confirm == 'Y') {
                    if (deleteMember(memberId)) {
                        std::cout << "Member deleted successfully!" << std::endl;
                    } else {
                        std::cout << "Failed to delete member." << std::endl;
                    }
                } else {
                    std::cout << "Delete cancelled." << std::endl;
                }
            } else {
                std::cout << "Member not found!" << std::endl;
            }
        }
        else if (choice == 6) {
            break;
        }
    }
}
