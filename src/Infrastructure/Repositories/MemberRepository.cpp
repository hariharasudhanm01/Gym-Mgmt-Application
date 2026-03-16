#include "../../../include/Infrastructure/Repositories/MemberRepository.h"
#include "../../../include/Infrastructure/Database/DatabaseManager.h"
#include <iostream>

Member MemberRepository::getById(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT m.member_id, m.user_id, m.age, m.height, m.weight, m.trainer_id, m.membership_type, "
                        "u.name, u.email, u.phone, u.password "
                        "FROM Members m JOIN Users u ON m.user_id = u.user_id WHERE m.member_id = " + std::to_string(id);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    Member member;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        member.setMemberId(sqlite3_column_int(stmt, 0));
        member.setUserId(sqlite3_column_int(stmt, 1));
        member.setAge(sqlite3_column_int(stmt, 2));
        member.setHeight(sqlite3_column_double(stmt, 3));
        member.setWeight(sqlite3_column_double(stmt, 4));
        member.setTrainerId(sqlite3_column_int(stmt, 5));
        member.setMembershipType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        member.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        member.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        member.setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        member.setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        member.setRole(Role::Member);
    }
    db->finalizeStatement(stmt);
    return member;
}

Member MemberRepository::getByUserId(int userId) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT m.member_id, m.user_id, m.age, m.height, m.weight, m.trainer_id, m.membership_type, "
                        "u.name, u.email, u.phone, u.password "
                        "FROM Members m JOIN Users u ON m.user_id = u.user_id WHERE m.user_id = " + std::to_string(userId);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    Member member;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        member.setMemberId(sqlite3_column_int(stmt, 0));
        member.setUserId(sqlite3_column_int(stmt, 1));
        member.setAge(sqlite3_column_int(stmt, 2));
        member.setHeight(sqlite3_column_double(stmt, 3));
        member.setWeight(sqlite3_column_double(stmt, 4));
        member.setTrainerId(sqlite3_column_int(stmt, 5));
        member.setMembershipType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        member.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        member.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        member.setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        member.setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        member.setRole(Role::Member);
    }
    db->finalizeStatement(stmt);
    return member;
}

std::vector<Member> MemberRepository::getByTrainerId(int trainerId) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT m.member_id, m.user_id, m.age, m.height, m.weight, m.trainer_id, m.membership_type, "
                        "u.name, u.email, u.phone, u.password "
                        "FROM Members m JOIN Users u ON m.user_id = u.user_id WHERE m.trainer_id = " + std::to_string(trainerId);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<Member> members;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        Member member;
        member.setMemberId(sqlite3_column_int(stmt, 0));
        member.setUserId(sqlite3_column_int(stmt, 1));
        member.setAge(sqlite3_column_int(stmt, 2));
        member.setHeight(sqlite3_column_double(stmt, 3));
        member.setWeight(sqlite3_column_double(stmt, 4));
        member.setTrainerId(sqlite3_column_int(stmt, 5));
        member.setMembershipType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        member.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        member.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        member.setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        member.setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        member.setRole(Role::Member);
        members.push_back(member);
    }
    db->finalizeStatement(stmt);
    return members;
}

std::vector<Member> MemberRepository::getAll() {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT m.member_id, m.user_id, m.age, m.height, m.weight, m.trainer_id, m.membership_type, "
                        "u.name, u.email, u.phone, u.password "
                        "FROM Members m JOIN Users u ON m.user_id = u.user_id";
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<Member> members;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        Member member;
        member.setMemberId(sqlite3_column_int(stmt, 0));
        member.setUserId(sqlite3_column_int(stmt, 1));
        member.setAge(sqlite3_column_int(stmt, 2));
        member.setHeight(sqlite3_column_double(stmt, 3));
        member.setWeight(sqlite3_column_double(stmt, 4));
        member.setTrainerId(sqlite3_column_int(stmt, 5));
        member.setMembershipType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        member.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        member.setEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        member.setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        member.setPassword(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        member.setRole(Role::Member);
        members.push_back(member);
    }
    db->finalizeStatement(stmt);
    return members;
}

bool MemberRepository::add(const Member& member) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "INSERT INTO Members (user_id, age, height, weight, trainer_id, membership_type) VALUES (" +
                        std::to_string(member.getUserId()) + ", " +
                        std::to_string(member.getAge()) + ", " +
                        std::to_string(member.getHeight()) + ", " +
                        std::to_string(member.getWeight()) + ", " +
                        std::to_string(member.getTrainerId()) + ", '" +
                        member.getMembershipType() + "')";
    return db->executeQuery(query);
}

bool MemberRepository::update(const Member& member) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "UPDATE Members SET "
                        "age = " + std::to_string(member.getAge()) + ", "
                        "height = " + std::to_string(member.getHeight()) + ", "
                        "weight = " + std::to_string(member.getWeight()) + ", "
                        "trainer_id = " + std::to_string(member.getTrainerId()) + ", "
                        "membership_type = '" + member.getMembershipType() + "' "
                        "WHERE member_id = " + std::to_string(member.getMemberId());
    return db->executeQuery(query);
}

bool MemberRepository::remove(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "DELETE FROM Members WHERE member_id = " + std::to_string(id);
    return db->executeQuery(query);
}
