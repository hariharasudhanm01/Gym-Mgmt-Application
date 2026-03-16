#ifndef I_REPOSITORY_H
#define I_REPOSITORY_H

#include <vector>

template <typename T>
class IRepository {
public:
    virtual ~IRepository() = default;
    
    virtual T getById(int id) = 0;
    virtual std::vector<T> getAll() = 0;
    virtual bool add(const T& entity) = 0;
    virtual bool update(const T& entity) = 0;
    virtual bool remove(int id) = 0;
};

#endif
