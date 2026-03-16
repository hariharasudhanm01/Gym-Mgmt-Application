#ifndef RATING_REPOSITORY_H
#define RATING_REPOSITORY_H

#include "../../Domain/Interfaces/IRepository.h"
#include "../../Domain/Entities/TrainerRating.h"
#include <vector>

class RatingRepository : public IRepository<TrainerRating> {
public:
    RatingRepository() = default;
    ~RatingRepository() override = default;

    TrainerRating getById(int id) override;
    std::vector<TrainerRating> getAll() override;
    std::vector<TrainerRating> getByTrainerId(int trainerId);
    bool add(const TrainerRating& entity) override;
    bool update(const TrainerRating& entity) override;
    bool remove(int id) override;
};

#endif
