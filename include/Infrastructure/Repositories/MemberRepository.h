#ifndef MEMBER_REPOSITORY_H
#define MEMBER_REPOSITORY_H

#include "../../Domain/Interfaces/IRepository.h"
#include "../../Domain/Entities/Member.h"
#include <memory>

class MemberRepository : public IRepository<Member> {
public:
    MemberRepository() = default;
    ~MemberRepository() override = default;

    Member getById(int id) override;
    Member getByUserId(int userId);
    std::vector<Member> getAll() override;
    std::vector<Member> getByTrainerId(int trainerId);
    bool add(const Member& entity) override;
    bool update(const Member& entity) override;
    bool remove(int id) override;
};

#endif
