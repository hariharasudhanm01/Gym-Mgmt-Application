#include "../include/HealthModule.h"
#include "../libs/sqlite/sqlite3.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>

HealthModule::HealthModule(DatabaseManager& database) : db(database) {}

std::string HealthModule::getCurrentDate() {
    time_t now = time(0);
    std::tm* timeinfo = localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d");
    return oss.str();
}

double HealthModule::calculateBMI(double weight, double height) {
    // BMI = weight (kg) / (height (m))^2
    // If height is in cm, convert to meters
    if (height > 100) height = height / 100.0;
    
    if (height <= 0) return 0;
    return weight / (height * height);
}

std::string HealthModule::getBMICategory(double bmi) {
    if (bmi < 18.5) return "Underweight";
    if (bmi < 25.0) return "Normal Weight";
    if (bmi < 30.0) return "Overweight";
    return "Obese";
}

bool HealthModule::recordHealth(int memberId, double height, double weight) {
    double bmi = calculateBMI(weight, height);
    std::string category = getBMICategory(bmi);
    std::string recordDate = getCurrentDate();
    
    std::ostringstream query;
    query << "INSERT INTO healthRecords (memberId, height, weight, bmi, category, recordDate) "
          << "VALUES (" << memberId << ", " << height << ", " << weight << ", " 
          << std::fixed << std::setprecision(2) << bmi << ", '" << category << "', '" 
          << recordDate << "');";
    
    if (!db.executeQuery(query.str())) {
        std::cout << "Error recording health data." << std::endl;
        return false;
    }
    
    std::cout << "Health record added successfully!" << std::endl;
    std::cout << "BMI: " << std::fixed << std::setprecision(2) << bmi << " (" << category << ")" << std::endl;
    return true;
}

bool HealthModule::getLatestHealthRecord(int memberId, HealthRecord& record) {
    std::ostringstream query;
    query << "SELECT id, memberId, height, weight, bmi, category, recordDate "
          << "FROM healthRecords WHERE memberId = " << memberId 
          << " ORDER BY recordDate DESC LIMIT 1;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query.str());
    if (!stmt) return false;
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        record.id = sqlite3_column_int(stmt, 0);
        record.memberId = sqlite3_column_int(stmt, 1);
        record.height = sqlite3_column_double(stmt, 2);
        record.weight = sqlite3_column_double(stmt, 3);
        record.bmi = sqlite3_column_double(stmt, 4);
        record.category = (char*)sqlite3_column_text(stmt, 5);
        record.recordDate = (char*)sqlite3_column_text(stmt, 6);
        
        db.finalizeStatement(stmt);
        return true;
    }
    
    db.finalizeStatement(stmt);
    return false;
}

bool HealthModule::getAllHealthRecords(int memberId, std::vector<HealthRecord>& records) {
    std::ostringstream query;
    query << "SELECT id, memberId, height, weight, bmi, category, recordDate "
          << "FROM healthRecords WHERE memberId = " << memberId 
          << " ORDER BY recordDate DESC;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query.str());
    if (!stmt) return false;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        HealthRecord record;
        record.id = sqlite3_column_int(stmt, 0);
        record.memberId = sqlite3_column_int(stmt, 1);
        record.height = sqlite3_column_double(stmt, 2);
        record.weight = sqlite3_column_double(stmt, 3);
        record.bmi = sqlite3_column_double(stmt, 4);
        record.category = (char*)sqlite3_column_text(stmt, 5);
        record.recordDate = (char*)sqlite3_column_text(stmt, 6);
        
        records.push_back(record);
    }
    
    db.finalizeStatement(stmt);
    return true;
}

void HealthModule::displayHealthMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n=== HEALTH & BMI MANAGEMENT ===" << std::endl;
        std::cout << "1. Record Health Data" << std::endl;
        std::cout << "2. View Health History" << std::endl;
        std::cout << "3. BMI Chart" << std::endl;
        std::cout << "4. Back to Main Menu" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        
        if (choice == 1) {
            int memberId;
            double height, weight;
            
            std::cout << "Member ID: ";
            std::cin >> memberId;
            std::cout << "Height (cm): ";
            std::cin >> height;
            std::cout << "Weight (kg): ";
            std::cin >> weight;
            
            recordHealth(memberId, height, weight);
        }
        else if (choice == 2) {
            int memberId;
            std::cout << "Member ID: ";
            std::cin >> memberId;
            
            std::vector<HealthRecord> records;
            if (getAllHealthRecords(memberId, records) && !records.empty()) {
                std::cout << "\n=== HEALTH HISTORY ===" << std::endl;
                std::cout << std::string(80, '-') << std::endl;
                std::cout << "Date | Height | Weight | BMI | Category" << std::endl;
                std::cout << std::string(80, '-') << std::endl;
                
                for (const auto& record : records) {
                    std::cout << record.recordDate << " | " << record.height 
                              << " | " << record.weight << " | " 
                              << std::fixed << std::setprecision(2) << record.bmi 
                              << " | " << record.category << std::endl;
                }
            } else {
                std::cout << "No health records found for this member." << std::endl;
            }
        }
        else if (choice == 3) {
            displayBMIChart();
        }
        else if (choice == 4) {
            break;
        }
    }
}

void HealthModule::displayBMIChart() {
    std::cout << "\n=== BMI CHART ===" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Category | BMI Range" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Underweight | BMI < 18.5" << std::endl;
    std::cout << "Normal Weight | 18.5 <= BMI < 25.0" << std::endl;
    std::cout << "Overweight | 25.0 <= BMI < 30.0" << std::endl;
    std::cout << "Obese | BMI >= 30.0" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
}

// MVP: Generate personalized health insights for a member
void HealthModule::displayHealthInsights(int memberId) {
    std::vector<HealthRecord> records;
    if (!getAllHealthRecords(memberId, records) || records.empty()) {
        std::cout << "No health data available for insights." << std::endl;
        return;
    }

    std::cout << "\n=== PERSONALIZED HEALTH INSIGHTS ===" << std::endl;
    const HealthRecord& latest = records.front();
    const HealthRecord& oldest = records.back();

    double bmiChange = latest.bmi - oldest.bmi;
    double weightChange = latest.weight - oldest.weight;
    std::cout << "From " << oldest.recordDate << " to " << latest.recordDate << ":\n";
    if (bmiChange > 1.0) {
        std::cout << "- Your BMI increased by " << std::fixed << std::setprecision(2) << bmiChange << ". ";
        std::cout << "(" << oldest.bmi << " -> " << latest.bmi << ")\n";
    } else if (bmiChange < -1.0) {
        std::cout << "- Your BMI decreased by " << std::fixed << std::setprecision(2) << -bmiChange << ". ";
        std::cout << "(" << oldest.bmi << " -> " << latest.bmi << ")\n";
    } else {
        std::cout << "- Your BMI remained stable. (" << latest.bmi << ")\n";
    }

    if (weightChange > 1.0) {
        std::cout << "- You gained " << std::fixed << std::setprecision(2) << weightChange << " kg. ";
        std::cout << "(" << oldest.weight << " -> " << latest.weight << ")\n";
    } else if (weightChange < -1.0) {
        std::cout << "- You lost " << std::fixed << std::setprecision(2) << -weightChange << " kg. ";
        std::cout << "(" << oldest.weight << " -> " << latest.weight << ")\n";
    } else {
        std::cout << "- Your weight remained stable. (" << latest.weight << " kg)\n";
    }

    // Category change
    if (latest.category != oldest.category) {
        std::cout << "- BMI Category changed: " << oldest.category << " -> " << latest.category << "\n";
    } else {
        std::cout << "- BMI Category: " << latest.category << "\n";
    }

    // Trend analysis (simple)
    if (records.size() >= 3) {
        int up = 0, down = 0;
        for (size_t i = 1; i < records.size(); ++i) {
            if (records[i-1].bmi < records[i].bmi) up++;
            else if (records[i-1].bmi > records[i].bmi) down++;
        }
        if (up > down) std::cout << "- Recent trend: BMI increasing.\n";
        else if (down > up) std::cout << "- Recent trend: BMI decreasing.\n";
        else std::cout << "- Recent trend: BMI stable.\n";
    }

    // Health tip
    if (latest.category == "Obese") {
        std::cout << "Tip: Consider consulting a nutritionist and increasing physical activity.\n";
    } else if (latest.category == "Underweight") {
        std::cout << "Tip: Ensure adequate calorie intake and consult a healthcare provider.\n";
    } else if (latest.category == "Normal Weight") {
        std::cout << "Tip: Keep up the good work maintaining a healthy BMI!\n";
    } else if (latest.category == "Overweight") {
        std::cout << "Tip: Moderate exercise and balanced diet can help reach a normal BMI.\n";
    }
}

