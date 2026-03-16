#include "../../../include/Infrastructure/Repositories/WorkoutRepository.h"
#include "../../../include/Infrastructure/Database/DatabaseManager.h"

WorkoutPlan WorkoutRepository::getById(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT plan_id, member_id, trainer_id, exercise_list, duration_weeks, difficulty_level "
                        "FROM WorkoutPlans WHERE plan_id = " + std::to_string(id);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    WorkoutPlan plan;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        plan.setPlanId(sqlite3_column_int(stmt, 0));
        plan.setMemberId(sqlite3_column_int(stmt, 1));
        plan.setTrainerId(sqlite3_column_int(stmt, 2));
        if (sqlite3_column_text(stmt, 3)) plan.setExerciseList(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        plan.setDurationWeeks(sqlite3_column_int(stmt, 4));
        if (sqlite3_column_text(stmt, 5)) plan.setDifficultyLevel(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
    }
    db->finalizeStatement(stmt);
    return plan;
}

std::vector<WorkoutPlan> WorkoutRepository::getAll() {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT plan_id, member_id, trainer_id, exercise_list, duration_weeks, difficulty_level FROM WorkoutPlans";
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<WorkoutPlan> plans;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        WorkoutPlan plan;
        plan.setPlanId(sqlite3_column_int(stmt, 0));
        plan.setMemberId(sqlite3_column_int(stmt, 1));
        plan.setTrainerId(sqlite3_column_int(stmt, 2));
        if (sqlite3_column_text(stmt, 3)) plan.setExerciseList(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        plan.setDurationWeeks(sqlite3_column_int(stmt, 4));
        if (sqlite3_column_text(stmt, 5)) plan.setDifficultyLevel(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        plans.push_back(plan);
    }
    db->finalizeStatement(stmt);
    return plans;
}

std::vector<WorkoutPlan> WorkoutRepository::getByMemberId(int memberId) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT plan_id, member_id, trainer_id, exercise_list, duration_weeks, difficulty_level "
                        "FROM WorkoutPlans WHERE member_id = " + std::to_string(memberId);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<WorkoutPlan> plans;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        WorkoutPlan plan;
        plan.setPlanId(sqlite3_column_int(stmt, 0));
        plan.setMemberId(sqlite3_column_int(stmt, 1));
        plan.setTrainerId(sqlite3_column_int(stmt, 2));
        if (sqlite3_column_text(stmt, 3)) plan.setExerciseList(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        plan.setDurationWeeks(sqlite3_column_int(stmt, 4));
        if (sqlite3_column_text(stmt, 5)) plan.setDifficultyLevel(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        plans.push_back(plan);
    }
    db->finalizeStatement(stmt);
    return plans;
}

std::vector<WorkoutPlan> WorkoutRepository::getByTrainerId(int trainerId) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT plan_id, member_id, trainer_id, exercise_list, duration_weeks, difficulty_level "
                        "FROM WorkoutPlans WHERE trainer_id = " + std::to_string(trainerId);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<WorkoutPlan> plans;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        WorkoutPlan plan;
        plan.setPlanId(sqlite3_column_int(stmt, 0));
        plan.setMemberId(sqlite3_column_int(stmt, 1));
        plan.setTrainerId(sqlite3_column_int(stmt, 2));
        if (sqlite3_column_text(stmt, 3)) plan.setExerciseList(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        plan.setDurationWeeks(sqlite3_column_int(stmt, 4));
        if (sqlite3_column_text(stmt, 5)) plan.setDifficultyLevel(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        plans.push_back(plan);
    }
    db->finalizeStatement(stmt);
    return plans;
}

bool WorkoutRepository::add(const WorkoutPlan& plan) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "INSERT INTO WorkoutPlans (member_id, trainer_id, exercise_list, duration_weeks, difficulty_level) VALUES (" +
                        std::to_string(plan.getMemberId()) + ", " +
                        std::to_string(plan.getTrainerId()) + ", '" +
                        plan.getExerciseList() + "', " +
                        std::to_string(plan.getDurationWeeks()) + ", '" +
                        plan.getDifficultyLevel() + "')";
    return db->executeQuery(query);
}

bool WorkoutRepository::update(const WorkoutPlan& plan) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "UPDATE WorkoutPlans SET "
                        "member_id = " + std::to_string(plan.getMemberId()) + ", "
                        "trainer_id = " + std::to_string(plan.getTrainerId()) + ", "
                        "exercise_list = '" + plan.getExerciseList() + "', "
                        "duration_weeks = " + std::to_string(plan.getDurationWeeks()) + ", "
                        "difficulty_level = '" + plan.getDifficultyLevel() + "' "
                        "WHERE plan_id = " + std::to_string(plan.getPlanId());
    return db->executeQuery(query);
}

bool WorkoutRepository::remove(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "DELETE FROM WorkoutPlans WHERE plan_id = " + std::to_string(id);
    return db->executeQuery(query);
}
