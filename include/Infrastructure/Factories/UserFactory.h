#ifndef USERFACTORY_H
#define USERFACTORY_H

#include "../../Domain/Entities/User.h"
#include "../../Domain/Entities/Admin.h"
#include "../../Domain/Entities/Trainer.h"
#include "../../Domain/Entities/Member.h"
#include <memory>

class UserFactory {
public:
    static std::unique_ptr<User> createUser(Role role) {
        switch (role) {
            case Role::Admin:
                return std::make_unique<Admin>();
            case Role::Trainer:
                return std::make_unique<Trainer>();
            case Role::Member:
                return std::make_unique<Member>();
            default:
                return nullptr;
        }
    }
};

#endif
