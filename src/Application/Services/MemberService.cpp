#include "../../../include/Application/Services/MemberService.h"

std::vector<HealthProgress> MemberService::viewHealthProgress(int userId) {
    auto member = memberRepo.getByUserId(userId);
    return progressRepo.getByMemberId(member.getMemberId());
}

std::vector<WorkoutPlan> MemberService::viewWorkoutPlan(int userId) {
    auto member = memberRepo.getByUserId(userId);
    return workoutRepo.getByMemberId(member.getMemberId());
}

std::vector<Trainer> MemberService::viewTrainerRatings() {
    auto trainers = trainerRepo.getAll();
    if(ratingStrategy != nullptr) {
        for(auto& trainer : trainers) {
            auto ratings = ratingRepo.getByTrainerId(trainer.getTrainerId());
            double newRating = ratingStrategy->calculateRating(ratings);
            if(newRating != trainer.getRating()) {
                trainer.setRating(newRating);
                trainerRepo.update(trainer);
            }
        }
    }
    return trainers;
}

bool MemberService::chooseTrainerBasedOnRating(int userId, int trainerId) {
    auto member = memberRepo.getByUserId(userId);
    if(member.getMemberId() == 0) return false;
    
    auto trainer = trainerRepo.getById(trainerId);
    if(trainer.getTrainerId() == 0) return false;
    
    member.setTrainerId(trainerId);
    return memberRepo.update(member);
}

bool MemberService::updateHealthMetrics(int userId, double weight, double bodyFat, double muscleMass, const std::string& date) {
    auto member = memberRepo.getByUserId(userId);
    if(member.getMemberId() == 0) return false;
    HealthProgress progress(0, member.getMemberId(), weight, bodyFat, muscleMass, date);
    return progressRepo.add(progress);
}

bool MemberService::rateTrainer(int userId, int trainerId, double score, const std::string& review) {
    auto member = memberRepo.getByUserId(userId);
    if(member.getMemberId() == 0) return false;
    TrainerRating rating(0, trainerId, member.getMemberId(), score, review);
    return ratingRepo.add(rating);
}

double MemberService::calculateBMI(int userId) {
    auto member = memberRepo.getByUserId(userId);
    if (member.getMemberId() == 0) return 0.0;
    
    double h = member.getHeight();
    double w = member.getWeight();
    
    if (h <= 0 || w <= 0) return 0.0;
    
    // Assume height > 3.0 means cm.
    if (h > 3.0) {
        h = h / 100.0;
    }
    
    return w / (h * h);
}
