#ifndef AVERAGE_RATING_STRATEGY_H
#define AVERAGE_RATING_STRATEGY_H

#include "../../Domain/Interfaces/IRatingStrategy.h"

// Concrete implementation of IRatingStrategy
class AverageRatingStrategy : public IRatingStrategy {
public:
    double calculateRating(const std::vector<TrainerRating>& ratings) override {
        if (ratings.empty()) {
            return 0.0;
        }

        double totalScore = 0.0;
        for (const auto& rating : ratings) {
            totalScore += rating.getRatingScore();
        }

        return totalScore / ratings.size();
    }
};

#endif
