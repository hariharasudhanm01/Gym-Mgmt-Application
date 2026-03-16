#include "../../../include/Application/Services/TrainerService.h"

std::vector<Member> TrainerService::viewAssignedMembers(int userId) {
    auto trainer = trainerRepo.getByUserId(userId);
    return memberRepo.getByTrainerId(trainer.getTrainerId());
}

bool TrainerService::createWorkoutPlan(int userId, int memberId, const std::string& exercises, int durationWeeks, const std::string& difficulty) {
    auto trainer = trainerRepo.getByUserId(userId);
    if(trainer.getTrainerId() == 0) return false;
    WorkoutPlan plan(0, memberId, trainer.getTrainerId(), exercises, durationWeeks, difficulty);
    return workoutRepo.add(plan);
}

bool TrainerService::updateWorkoutPlan(int planId, const std::string& exercises, int durationWeeks, const std::string& difficulty) {
    WorkoutPlan plan = workoutRepo.getById(planId);
    if(plan.getPlanId() == 0) return false;
    
    plan.setExerciseList(exercises);
    plan.setDurationWeeks(durationWeeks);
    plan.setDifficultyLevel(difficulty);
    return workoutRepo.update(plan);
}

std::vector<HealthProgress> TrainerService::trackMemberProgress(int memberId) {
    return progressRepo.getByMemberId(memberId);
}

bool TrainerService::updateMemberProgress(int memberId, double weight, double bodyFat, double muscleMass, const std::string& date) {
    HealthProgress progress(0, memberId, weight, bodyFat, muscleMass, date);
    return progressRepo.add(progress);
}

std::vector<TrainerRating> TrainerService::viewRatings(int userId) {
    auto trainer = trainerRepo.getByUserId(userId);
    return ratingRepo.getByTrainerId(trainer.getTrainerId());
}
