#ifndef PROGRESS_MODULE_H
#define PROGRESS_MODULE_H

#include <string>
#include <vector>
#include "DatabaseManager.h"

struct ProgressRecord {
    int id;
    int memberId;
    double weight;
    double bmi;
    std::string achievement;
    std::string recordDate;
};

class ProgressModule {
private:
    DatabaseManager& db;
    
public:
    ProgressModule(DatabaseManager& database);
    
    bool recordProgress(int memberId, double weight, const std::string& achievement = "");
    bool getProgressHistory(int memberId, std::vector<ProgressRecord>& records);
    bool getLatestProgress(int memberId, ProgressRecord& record);
    double calculateWeightChange(int memberId);
    double calculateBMIChange(int memberId);
    bool addAchievement(int memberId, const std::string& achievement);
    void displayProgressMenu();
    void displayMemberProgress(int memberId);
    
private:
    std::string getCurrentDate();
};

#endif
