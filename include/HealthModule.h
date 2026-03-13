#ifndef HEALTH_MODULE_H
#define HEALTH_MODULE_H

#include <string>
#include "DatabaseManager.h"

struct HealthRecord {
    int id;
    int memberId;
    double height;
    double weight;
    double bmi;
    std::string category; // Underweight, Normal, Overweight, Obese
    std::string recordDate;
};

class HealthModule {
private:
    DatabaseManager& db;
    
public:
    HealthModule(DatabaseManager& database);
    
    double calculateBMI(double weight, double height);
    std::string getBMICategory(double bmi);
    bool recordHealth(int memberId, double height, double weight);
    bool getLatestHealthRecord(int memberId, HealthRecord& record);
    bool getAllHealthRecords(int memberId, std::vector<HealthRecord>& records);
    void displayHealthMenu();
    void displayBMIChart();
    void displayHealthInsights(int memberId);
    
private:
    std::string getCurrentDate();
};

#endif
