#include "../include/ProgressModule.h"
#include "../libs/sqlite/sqlite3.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cmath>

ProgressModule::ProgressModule(DatabaseManager& database) : db(database) {}

std::string ProgressModule::getCurrentDate() {
    time_t now = time(0);
    std::tm* timeinfo = localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d");
    return oss.str();
}

bool ProgressModule::recordProgress(int memberId, double weight, const std::string& achievement) {
    // Calculate BMI from latest health record
    std::ostringstream healthQuery;
    healthQuery << "SELECT bmi FROM healthRecords WHERE memberId = " << memberId 
                << " ORDER BY recordDate DESC LIMIT 1;";
    
    sqlite3_stmt* healthStmt = db.prepareStatement(healthQuery.str());
    double bmi = 0.0;
    
    if (healthStmt && sqlite3_step(healthStmt) == SQLITE_ROW) {
        bmi = sqlite3_column_double(healthStmt, 0);
    }
    db.finalizeStatement(healthStmt);
    
    std::string recordDate = getCurrentDate();
    
    std::ostringstream query;
    query << "INSERT INTO progressRecords (memberId, weight,bmi, achievement, recordDate) "
          << "VALUES (" << memberId << ", " << weight << ", " << std::fixed 
          << std::setprecision(2) << bmi << ", '" << achievement << "', '" 
          << recordDate << "');";
    
    if (!db.executeQuery(query.str())) {
        std::cout << "Error recording progress." << std::endl;
        return false;
    }
    
    std::cout << "Progress recorded successfully!" << std::endl;
    return true;
}

bool ProgressModule::getProgressHistory(int memberId, std::vector<ProgressRecord>& records) {
    std::ostringstream query;
    query << "SELECT id, memberId, weight, bmi, achievement, recordDate FROM progressRecords "
          << "WHERE memberId = " << memberId << " ORDER BY recordDate DESC;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query.str());
    if (!stmt) return false;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        ProgressRecord record;
        record.id = sqlite3_column_int(stmt, 0);
        record.memberId = sqlite3_column_int(stmt, 1);
        record.weight = sqlite3_column_double(stmt, 2);
        record.bmi = sqlite3_column_double(stmt, 3);
        record.achievement = (char*)sqlite3_column_text(stmt, 4);
        record.recordDate = (char*)sqlite3_column_text(stmt, 5);
        
        records.push_back(record);
    }
    
    db.finalizeStatement(stmt);
    return true;
}

bool ProgressModule::getLatestProgress(int memberId, ProgressRecord& record) {
    std::ostringstream query;
    query << "SELECT id, memberId, weight, bmi, achievement, recordDate FROM progressRecords "
          << "WHERE memberId = " << memberId << " ORDER BY recordDate DESC LIMIT 1;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query.str());
    if (!stmt) return false;
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        record.id = sqlite3_column_int(stmt, 0);
        record.memberId = sqlite3_column_int(stmt, 1);
        record.weight = sqlite3_column_double(stmt, 2);
        record.bmi = sqlite3_column_double(stmt, 3);
        record.achievement = (char*)sqlite3_column_text(stmt, 4);
        record.recordDate = (char*)sqlite3_column_text(stmt, 5);
        
        db.finalizeStatement(stmt);
        return true;
    }
    
    db.finalizeStatement(stmt);
    return false;
}

double ProgressModule::calculateWeightChange(int memberId) {
    const char* query = "SELECT weight FROM progressRecords WHERE memberId = ? ORDER BY recordDate;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query);
    if (!stmt) return 0.0;
    
    std::ostringstream oss;
    oss << "SELECT weight FROM progressRecords WHERE memberId = " << memberId 
        << " ORDER BY recordDate;";
    
    sqlite3_stmt* stmt2 = db.prepareStatement(oss.str());
    if (!stmt2) return 0.0;
    
    double firstWeight = 0.0, lastWeight = 0.0;
    bool isFirst = true;
    
    while (sqlite3_step(stmt2) == SQLITE_ROW) {
        double weight = sqlite3_column_double(stmt2, 0);
        if (isFirst) {
            firstWeight = weight;
            isFirst = false;
        }
        lastWeight = weight;
    }
    
    db.finalizeStatement(stmt2);
    
    return lastWeight - firstWeight;
}

double ProgressModule::calculateBMIChange(int memberId) {
    std::ostringstream oss;
    oss << "SELECT bmi FROM progressRecords WHERE memberId = " << memberId 
        << " ORDER BY recordDate;";
    
    sqlite3_stmt* stmt = db.prepareStatement(oss.str());
    if (!stmt) return 0.0;
    
    double firstBMI = 0.0, lastBMI = 0.0;
    bool isFirst = true;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        double bmi = sqlite3_column_double(stmt, 0);
        if (isFirst) {
            firstBMI = bmi;
            isFirst = false;
        }
        lastBMI = bmi;
    }
    
    db.finalizeStatement(stmt);
    
    return lastBMI - firstBMI;
}

bool ProgressModule::addAchievement(int memberId, const std::string& achievement) {
    std::ostringstream query;
    query << "UPDATE progressRecords SET achievement = '" << achievement 
          << "' WHERE memberId = " << memberId 
          << " ORDER BY recordDate DESC LIMIT 1;";
    
    if (!db.executeQuery(query.str())) {
        std::cout << "Error adding achievement." << std::endl;
        return false;
    }
    
    std::cout << "Achievement recorded!" << std::endl;
    return true;
}

void ProgressModule::displayProgressMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n=== PROGRESS TRACKING ===" << std::endl;
        std::cout << "1. Record Progress" << std::endl;
        std::cout << "2. View Progress History" << std::endl;
        std::cout << "3. View Member Progress Summary" << std::endl;
        std::cout << "4. Add Achievement" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        
        if (choice == 1) {
            int memberId;
            double weight;
            std::string achievement;
            
            std::cout << "Member ID: ";
            std::cin >> memberId;
            std::cout << "Current Weight (kg): ";
            std::cin >> weight;
            std::cout << "Achievement (optional, leave empty to skip): ";
            std::cin.ignore();
            std::getline(std::cin, achievement);
            
            recordProgress(memberId, weight, achievement);
        }
        else if (choice == 2) {
            int memberId;
            std::cout << "Member ID: ";
            std::cin >> memberId;
            
            std::vector<ProgressRecord> records;
            if (getProgressHistory(memberId, records) && !records.empty()) {
                std::cout << "\n=== PROGRESS HISTORY ===" << std::endl;
                std::cout << std::string(80, '-') << std::endl;
                std::cout << "Date | Weight | BMI | Achievement" << std::endl;
                std::cout << std::string(80, '-') << std::endl;
                
                for (const auto& record : records) {
                    std::cout << record.recordDate << " | " << record.weight 
                              << " | " << std::fixed << std::setprecision(2) << record.bmi 
                              << " | " << record.achievement << std::endl;
                }
            } else {
                std::cout << "No progress records found for this member." << std::endl;
            }
        }
        else if (choice == 3) {
            int memberId;
            std::cout << "Member ID: ";
            std::cin >> memberId;
            
            displayMemberProgress(memberId);
        }
        else if (choice == 4) {
            int memberId;
            std::string achievement;
            
            std::cout << "Member ID: ";
            std::cin >> memberId;
            std::cout << "Achievement: ";
            std::cin.ignore();
            std::getline(std::cin, achievement);
            
            addAchievement(memberId, achievement);
        }
        else if (choice == 5) {
            break;
        }
    }
}

void ProgressModule::displayMemberProgress(int memberId) {
    std::cout << "\n=== MEMBER PROGRESS SUMMARY ===" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    ProgressRecord latest;
    if (getLatestProgress(memberId, latest)) {
        std::cout << "Current Weight: " << latest.weight << " kg" << std::endl;
        std::cout << "Current BMI: " << std::fixed << std::setprecision(2) << latest.bmi << std::endl;
        std::cout << "Latest Achievement: " << latest.achievement << std::endl;
        std::cout << "Last Update: " << latest.recordDate << std::endl;
        
        double weightChange = calculateWeightChange(memberId);
        double bmiChange = calculateBMIChange(memberId);
        
        std::cout << "\nTotal Weight Change: " << (weightChange >= 0 ? "+" : "") 
                  << weightChange << " kg" << std::endl;
        std::cout << "Total BMI Change: " << (bmiChange >= 0 ? "+" : "") 
                  << std::fixed << std::setprecision(2) << bmiChange << std::endl;
    } else {
        std::cout << "No progress records found for this member." << std::endl;
    }
    
    std::cout << std::string(50, '=') << std::endl;
}
