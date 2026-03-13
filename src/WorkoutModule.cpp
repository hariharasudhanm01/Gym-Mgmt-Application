#include "../include/WorkoutModule.h"
#include "../libs/sqlite/sqlite3.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

WorkoutModule::WorkoutModule(DatabaseManager& database) : db(database) {}

std::string WorkoutModule::getCurrentDate() {
    time_t now = time(0);
    std::tm* timeinfo = localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d");
    return oss.str();
}

bool WorkoutModule::createWorkoutPlan(int memberId, const std::string& planName, const std::string& difficulty) {
    std::string createdDate = getCurrentDate();
    
    std::ostringstream query;
    query << "INSERT INTO workoutPlans (memberId, planName, difficulty, createdDate) "
          << "VALUES (" << memberId << ", '" << planName << "', '" << difficulty 
          << "', '" << createdDate << "');";
    
    if (!db.executeQuery(query.str())) {
        std::cout << "Error creating workout plan." << std::endl;
        return false;
    }
    
    std::cout << "Workout plan created successfully!" << std::endl;
    return true;
}

bool WorkoutModule::addExerciseToCart(int planId, const std::string& name, int sets, int reps,
                                       const std::string& description, const std::string& muscleGroup) {
    std::ostringstream query;
    query << "INSERT INTO exercises (planId, name, sets, reps, description, muscleGroup) "
          << "VALUES (" << planId << ", '" << name << "', " << sets << ", " << reps 
          << ", '" << description << "', '" << muscleGroup << "');";
    
    if (!db.executeQuery(query.str())) {
        std::cout << "Error adding exercise." << std::endl;
        return false;
    }
    
    std::cout << "Exercise added to plan!" << std::endl;
    return true;
}

bool WorkoutModule::removeExerciseFromPlan(int exerciseId) {
    std::ostringstream query;
    query << "DELETE FROM exercises WHERE id = " << exerciseId << ";";
    
    if (!db.executeQuery(query.str())) {
        std::cout << "Error removing exercise." << std::endl;
        return false;
    }
    
    std::cout << "Exercise removed from plan!" << std::endl;
    return true;
}

bool WorkoutModule::getWorkoutPlan(int planId, WorkoutPlan& plan) {
    std::ostringstream query;
    query << "SELECT id, memberId, planName, difficulty, createdDate FROM workoutPlans "
          << "WHERE id = " << planId << " AND active = 1;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query.str());
    if (!stmt) return false;
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        plan.id = sqlite3_column_int(stmt, 0);
        plan.memberId = sqlite3_column_int(stmt, 1);
        plan.planName = (char*)sqlite3_column_text(stmt, 2);
        plan.difficulty = (char*)sqlite3_column_text(stmt, 3);
        plan.createdDate = (char*)sqlite3_column_text(stmt, 4);
        
        db.finalizeStatement(stmt);
        
        // Get exercises
        std::ostringstream exerciseQuery;
        exerciseQuery << "SELECT id, name, sets, reps, description, muscleGroup FROM exercises "
                      << "WHERE planId = " << planId << ";";
        
        sqlite3_stmt* exStmt = db.prepareStatement(exerciseQuery.str());
        if (exStmt) {
            while (sqlite3_step(exStmt) == SQLITE_ROW) {
                Exercise ex;
                ex.id = sqlite3_column_int(exStmt, 0);
                ex.name = (char*)sqlite3_column_text(exStmt, 1);
                ex.sets = sqlite3_column_int(exStmt, 2);
                ex.reps = sqlite3_column_int(exStmt, 3);
                ex.description = (char*)sqlite3_column_text(exStmt, 4);
                ex.muscleGroup = (char*)sqlite3_column_text(exStmt, 5);
                
                plan.exercises.push_back(ex);
            }
            db.finalizeStatement(exStmt);
        }
        
        return true;
    }
    
    db.finalizeStatement(stmt);
    return false;
}

bool WorkoutModule::getMemberWorkoutPlans(int memberId, std::vector<WorkoutPlan>& plans) {
    std::ostringstream query;
    query << "SELECT id, memberId, planName, difficulty, createdDate FROM workoutPlans "
          << "WHERE memberId = " << memberId << " AND active = 1;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query.str());
    if (!stmt) return false;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        WorkoutPlan plan;
        plan.id = sqlite3_column_int(stmt, 0);
        plan.memberId = sqlite3_column_int(stmt, 1);
        plan.planName = (char*)sqlite3_column_text(stmt, 2);
        plan.difficulty = (char*)sqlite3_column_text(stmt, 3);
        plan.createdDate = (char*)sqlite3_column_text(stmt, 4);
        
        plans.push_back(plan);
    }
    
    db.finalizeStatement(stmt);
    return true;
}

bool WorkoutModule::assignPlanToMember(int memberId, int planId) {
    // This is handled by createWorkoutPlan which associates a plan to a member
    std::cout << "Plan assigned to member!" << std::endl;
    return true;
}

void WorkoutModule::displayWorkoutMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n=== WORKOUT MANAGEMENT ===" << std::endl;
        std::cout << "1. Create Workout Plan" << std::endl;
        std::cout << "2. View Member's Plans" << std::endl;
        std::cout << "3. Add Exercise to Plan" << std::endl;
        std::cout << "4. View Sample Plans" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        
        if (choice == 1) {
            int memberId;
            std::string planName, difficulty;
            
            std::cout << "Member ID: ";
            std::cin >> memberId;
            std::cout << "Plan Name: ";
            std::cin.ignore();
            std::getline(std::cin, planName);
            std::cout << "Difficulty (Beginner/Intermediate/Advanced): ";
            std::getline(std::cin, difficulty);
            
            createWorkoutPlan(memberId, planName, difficulty);
        }
        else if (choice == 2) {
            int memberId;
            std::cout << "Member ID: ";
            std::cin >> memberId;
            
            std::vector<WorkoutPlan> plans;
            if (getMemberWorkoutPlans(memberId, plans) && !plans.empty()) {
                std::cout << "\n=== MEMBER'S WORKOUT PLANS ===" << std::endl;
                for (const auto& plan : plans) {
                    std::cout << "\nPlan ID: " << plan.id << ", Name: " << plan.planName 
                              << ", Difficulty: " << plan.difficulty << std::endl;
                    
                    WorkoutPlan fullPlan;
                    if (getWorkoutPlan(plan.id, fullPlan)) {
                        std::cout << "Exercises:" << std::endl;
                        for (const auto& ex : fullPlan.exercises) {
                            std::cout << "  - " << ex.name << " (" << ex.sets << "x" 
                                      << ex.reps << " reps) - " << ex.muscleGroup << std::endl;
                        }
                    }
                }
            } else {
                std::cout << "No workout plans found for this member." << std::endl;
            }
        }
        else if (choice == 3) {
            int planId, sets, reps;
            std::string name, description, muscleGroup;
            
            std::cout << "Plan ID: ";
            std::cin >> planId;
            std::cout << "Exercise Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Sets: ";
            std::cin >> sets;
            std::cout << "Reps: ";
            std::cin >> reps;
            std::cout << "Description: ";
            std::cin.ignore();
            std::getline(std::cin, description);
            std::cout << "Muscle Group: ";
            std::getline(std::cin, muscleGroup);
            
            addExerciseToCart(planId, name, sets, reps, description, muscleGroup);
        }
        else if (choice == 4) {
            displaySamplePlans();
        }
        else if (choice == 5) {
            break;
        }
    }
}

void WorkoutModule::displaySamplePlans() {
    std::cout << "\n=== SAMPLE WORKOUT PLANS ===" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "\n1. BEGINNER FULL BODY" << std::endl;
    std::cout << "   - Push-ups: 3x10 (Chest, Triceps)" << std::endl;
    std::cout << "   - Squats: 3x12 (Legs)" << std::endl;
    std::cout << "   - Walking Lunges: 3x10 (Legs)" << std::endl;
    std::cout << "   - Plank: 3x30s (Core)" << std::endl;
    
    std::cout << "\n2. INTERMEDIATE UPPER BODY" << std::endl;
    std::cout << "   - Bench Press: 4x8 (Chest)" << std::endl;
    std::cout << "   - Pull-ups: 4x6 (Back)" << std::endl;
    std::cout << "   - Dumbbell Curls: 3x10 (Biceps)" << std::endl;
    std::cout << "   - Tricep Dips: 3x8 (Triceps)" << std::endl;
    
    std::cout << "\n3. ADVANCED STRENGTH" << std::endl;
    std::cout << "   - Deadlifts: 5x5 (Full Body)" << std::endl;
    std::cout << "   - Barbell Squats: 5x5 (Legs)" << std::endl;
    std::cout << "   - Barbell Rows: 5x5 (Back)" << std::endl;
    
    std::cout << std::string(60, '=') << std::endl;
}
