#ifndef MEMBER_SERVICE_H
#define MEMBER_SERVICE_H

#include "../../Infrastructure/Repositories/MemberRepository.h"
#include "../../Infrastructure/Repositories/ProgressRepository.h"
#include "../../Infrastructure/Repositories/WorkoutRepository.h"
#include "../../Infrastructure/Repositories/TrainerRepository.h"
#include "../../Infrastructure/Repositories/RatingRepository.h"
#include "../../Domain/Interfaces/IRatingStrategy.h"
#include <vector>

class MemberService {
private:
    MemberRepository memberRepo;
    ProgressRepository progressRepo;
    WorkoutRepository workoutRepo;
    TrainerRepository trainerRepo;
    RatingRepository ratingRepo;
    IRatingStrategy* ratingStrategy;

public:
    MemberService(IRatingStrategy* strategy) : ratingStrategy(strategy) {}

    std::vector<HealthProgress> viewHealthProgress(int userId);
    std::vector<WorkoutPlan> viewWorkoutPlan(int userId);
    std::vector<Trainer> viewTrainerRatings();
    bool chooseTrainerBasedOnRating(int userId, int trainerId);
    bool updateHealthMetrics(int userId, double weight, double bodyFat, double muscleMass, const std::string& date);
    bool rateTrainer(int userId, int trainerId, double score, const std::string& review);
    double calculateBMI(int userId);
};

#endif
