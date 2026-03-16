#ifndef TRAINER_REPOSITORY_H
#define TRAINER_REPOSITORY_H

#include "../../Domain/Interfaces/IRepository.h"
#include "../../Domain/Entities/Trainer.h"
#include <memory>

class TrainerRepository : public IRepository<Trainer> {
public:
    TrainerRepository() = default;
    ~TrainerRepository() override = default;

    Trainer getById(int id) override;
    Trainer getByUserId(int userId);
    std::vector<Trainer> getAll() override;
    bool add(const Trainer& entity) override;
    bool update(const Trainer& entity) override;
    bool remove(int id) override;
};

#endif
