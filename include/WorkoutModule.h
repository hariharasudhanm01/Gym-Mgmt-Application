#ifndef WORKOUT_MODULE_H
#define WORKOUT_MODULE_H

#include <string>
#include <vector>
#include "DatabaseManager.h"
#include "Trainer.h"

struct Exercise {
    int id;
    std::string name;
    int sets;
    int reps;
    std::string description;
    std::string muscleGroup;
};

struct WorkoutPlan {
    int id;
    int memberId;
    std::string planName;
    std::string difficulty; // Beginner, Intermediate, Advanced
    std::string createdDate;
    std::vector<Exercise> exercises;
};

class WorkoutModule {
private:
    DatabaseManager& db;
    
public:
    WorkoutModule(DatabaseManager& database);
    
    bool createWorkoutPlan(int memberId, const std::string& planName, const std::string& difficulty);
    bool addExerciseToCart(int planId, const std::string& name, int sets, int reps,
                           const std::string& description, const std::string& muscleGroup);
    bool removeExerciseFromPlan(int exerciseId);
    bool getWorkoutPlan(int planId, WorkoutPlan& plan);
    bool getTopRatedTrainers(int memberId, std::vector<Trainer>& trainers);
    bool assignTrainer(int memberId, int trainerId);
    bool getMemberWorkoutPlans(int memberId, std::vector<WorkoutPlan> &plans);
    bool assignPlanToMember(int memberId, int planId);
    void displayWorkoutMenu();
    void displaySamplePlans();
    
private:
    std::string getCurrentDate();
};

#endif
