#ifndef USER_H
#define USER_H

#include <string>

enum class Role {
    Admin,
    Trainer,
    Member
};

class User {
protected:
    int userId;
    std::string name;
    std::string email;
    std::string phone;
    std::string password;
    Role role;

public:
    User() : userId(0) {}
    User(int id, const std::string& n, const std::string& e, const std::string& p, const std::string& pwd, Role r)
        : userId(id), name(n), email(e), phone(p), password(pwd), role(r) {}
    
    virtual ~User() = default;

    int getUserId() const { return userId; }
    void setUserId(int id) { userId = id; }
    
    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }
    
    std::string getEmail() const { return email; }
    void setEmail(const std::string& e) { email = e; }
    
    std::string getPhone() const { return phone; }
    void setPhone(const std::string& p) { phone = p; }
    
    std::string getPassword() const { return password; }
    void setPassword(const std::string& p) { password = p; }
    
    Role getRole() const { return role; }
    void setRole(Role r) { role = r; }

    virtual void login() = 0;
    virtual void logout() = 0;
};

#endif
