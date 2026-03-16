#ifndef TRAINER_SERVICE_H
#define TRAINER_SERVICE_H

#include "../../Infrastructure/Repositories/TrainerRepository.h"
#include "../../Infrastructure/Repositories/MemberRepository.h"
#include "../../Infrastructure/Repositories/WorkoutRepository.h"
#include "../../Infrastructure/Repositories/ProgressRepository.h"
#include "../../Infrastructure/Repositories/RatingRepository.h"
#include <vector>

class TrainerService {
private:
    TrainerRepository trainerRepo;
    MemberRepository memberRepo;
    WorkoutRepository workoutRepo;
    ProgressRepository progressRepo;
    RatingRepository ratingRepo;

public:
    TrainerService() = default;

    std::vector<Member> viewAssignedMembers(int userId);
    bool createWorkoutPlan(int userId, int memberId, const std::string& exercises, int durationWeeks, const std::string& difficulty);
    bool updateWorkoutPlan(int planId, const std::string& exercises, int durationWeeks, const std::string& difficulty);
    std::vector<HealthProgress> trackMemberProgress(int memberId);
    bool updateMemberProgress(int memberId, double weight, double bodyFat, double muscleMass, const std::string& date);
    std::vector<TrainerRating> viewRatings(int userId);
};

#endif
