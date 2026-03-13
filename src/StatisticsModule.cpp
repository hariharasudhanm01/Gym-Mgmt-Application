#include "../include/StatisticsModule.h"
#include "../libs/sqlite/sqlite3.h"
#include <iostream>
#include <iomanip>
#include <ctime>

StatisticsModule::StatisticsModule(DatabaseManager& database) : db(database) {}

std::string StatisticsModule::getCurrentDate() {
    time_t now = time(0);
    std::tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer);
}

int StatisticsModule::getTotalMembers() {
    const char* query = "SELECT COUNT(*) FROM members WHERE active = 1;";
    sqlite3_stmt* stmt = db.prepareStatement(query);
    
    if (!stmt) return 0;
    
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    
    db.finalizeStatement(stmt);
    return count;
}

int StatisticsModule::getActiveMembersCount() {
    std::string query = "SELECT COUNT(*) FROM members WHERE active = 1 AND "
                        "expiryDate >= '" + getCurrentDate() + "';";
    sqlite3_stmt* stmt = db.prepareStatement(query);
    
    if (!stmt) return 0;
    
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    
    db.finalizeStatement(stmt);
    return count;
}

double StatisticsModule::getAverageBMI() {
    const char* query = "SELECT AVG(bmi) FROM (SELECT DISTINCT memberId, bmi FROM healthRecords "
                        "ORDER BY memberId, recordDate DESC);";
    
    sqlite3_stmt* stmt = db.prepareStatement(query);
    if (!stmt) return 0.0;
    
    double avgBMI = 0.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        avgBMI = sqlite3_column_double(stmt, 0);
    }
    
    db.finalizeStatement(stmt);
    return avgBMI;
}

int StatisticsModule::getMembersInBMICategory(const std::string& category) {
    std::string query = "SELECT COUNT(DISTINCT memberId) FROM healthRecords WHERE category = '" 
                       + category + "' AND recordDate = (SELECT MAX(recordDate) FROM healthRecords hr2 "
                       "WHERE hr2.memberId = healthRecords.memberId);";
    
    sqlite3_stmt* stmt = db.prepareStatement(query);
    if (!stmt) return 0;
    
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    
    db.finalizeStatement(stmt);
    return count;
}

void StatisticsModule::displayStatistics() {
    std::cout << "\n=== GYM STATISTICS ===" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    int totalMembers = getTotalMembers();
    int activeMembers = getActiveMembersCount();
    double avgBMI = getAverageBMI();
    
    std::cout << "Total Members: " << totalMembers << std::endl;
    std::cout << "Active Members: " << activeMembers << std::endl;
    std::cout << "Average BMI: " << std::fixed << std::setprecision(2) << avgBMI << std::endl;
    
    std::cout << std::string(50, '=') << std::endl;
}

void StatisticsModule::displayMemberDistribution() {
    std::cout << "\n=== MEMBERSHIP DISTRIBUTION ===" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    const char* query = "SELECT membershipType, COUNT(*) FROM members WHERE active = 1 "
                        "GROUP BY membershipType;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query);
    if (!stmt) return;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string type = (char*)sqlite3_column_text(stmt, 0);
        int count = sqlite3_column_int(stmt, 1);
        std::cout << type << ": " << count << " members" << std::endl;
    }
    
    db.finalizeStatement(stmt);
    std::cout << std::string(50, '-') << std::endl;
}

void StatisticsModule::displayBMIDistribution() {
    std::cout << "\n=== BMI DISTRIBUTION ===" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    std::vector<std::string> categories = {"Underweight", "Normal Weight", "Overweight", "Obese"};
    
    for (const auto& category : categories) {
        int count = getMembersInBMICategory(category);
        std::cout << category << ": " << count << " members" << std::endl;
    }
    
    std::cout << std::string(50, '-') << std::endl;
}
