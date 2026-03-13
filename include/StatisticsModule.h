#ifndef STATISTICS_MODULE_H
#define STATISTICS_MODULE_H

#include <string>
#include "DatabaseManager.h"

class StatisticsModule {
private:
    DatabaseManager& db;
    
public:
    StatisticsModule(DatabaseManager& database);
    
    int getTotalMembers();
    int getActiveMembersCount();
    double getAverageBMI();
    int getMembersInBMICategory(const std::string& category);
    void displayStatistics();
    void displayMemberDistribution();
    void displayBMIDistribution();
    
private:
    std::string getCurrentDate();
};

#endif
