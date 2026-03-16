#ifndef PROGRESS_REPOSITORY_H
#define PROGRESS_REPOSITORY_H

#include "../../Domain/Interfaces/IRepository.h"
#include "../../Domain/Entities/HealthProgress.h"
#include <vector>

class ProgressRepository : public IRepository<HealthProgress> {
public:
    ProgressRepository() = default;
    ~ProgressRepository() override = default;

    HealthProgress getById(int id) override;
    std::vector<HealthProgress> getAll() override;
    std::vector<HealthProgress> getByMemberId(int memberId);
    bool add(const HealthProgress& entity) override;
    bool update(const HealthProgress& entity) override;
    bool remove(int id) override;
};

#endif
