#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "../../Domain/Interfaces/IRepository.h"
#include "../../Domain/Entities/User.h"
#include <memory>
#include <string>

class UserRepository : public IRepository<std::unique_ptr<User>> {
public:
    UserRepository();
    ~UserRepository() override = default;

    std::unique_ptr<User> getById(int id) override;
    std::unique_ptr<User> getByEmail(const std::string& email);
    std::vector<std::unique_ptr<User>> getAll() override;
    bool add(const std::unique_ptr<User>& entity) override;
    bool update(const std::unique_ptr<User>& entity) override;
    bool remove(int id) override;
};

#endif
