#ifndef I_RATING_STRATEGY_H
#define I_RATING_STRATEGY_H

#include <vector>
#include "../Entities/TrainerRating.h"

// Strategy Pattern Interface
class IRatingStrategy {
public:
    virtual ~IRatingStrategy() = default;
    
    // Calculates the score based on a list of ratings
    virtual double calculateRating(const std::vector<TrainerRating>& ratings) = 0;
};

#endif
