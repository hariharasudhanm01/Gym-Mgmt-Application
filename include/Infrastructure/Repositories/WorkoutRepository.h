#ifndef WORKOUT_REPOSITORY_H
#define WORKOUT_REPOSITORY_H

#include "../../Domain/Interfaces/IRepository.h"
#include "../../Domain/Entities/WorkoutPlan.h"
#include <vector>

class WorkoutRepository : public IRepository<WorkoutPlan> {
public:
    WorkoutRepository() = default;
    ~WorkoutRepository() override = default;

    WorkoutPlan getById(int id) override;
    std::vector<WorkoutPlan> getAll() override;
    std::vector<WorkoutPlan> getByMemberId(int memberId);
    std::vector<WorkoutPlan> getByTrainerId(int trainerId);
    bool add(const WorkoutPlan& entity) override;
    bool update(const WorkoutPlan& entity) override;
    bool remove(int id) override;
};

#endif
