#include "../include/AuthModule.h"
#include "../libs/sqlite/sqlite3.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <functional>

AuthModule::AuthModule(DatabaseManager& database)
    : db(database), currentUserId(0), currentUserRole(MEMBER), currentUsername("") {}

std::string AuthModule::hashPassword(const std::string& password) {
    // Simple hash - in production use bcrypt or similar
    return password; // For demo purposes, using plain text
}

bool AuthModule::registerUser(const std::string& username, const std::string& password, UserRole role) {
    std::string hashedPassword = hashPassword(password);
    
    time_t now = time(0);
    std::tm* timeinfo = localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    std::string createdDate = oss.str();
    
    std::string query = "INSERT INTO users (username, password, role, createdDate) VALUES ('" 
                       + username + "', '" + hashedPassword + "', " + std::to_string(role) 
                       + ", '" + createdDate + "');";
    
    if (!db.executeQuery(query)) {
        std::cout << "Registration failed. Username may already exist." << std::endl;
        return false;
    }
    
    std::cout << "User registered successfully!" << std::endl;
    return true;
}

bool AuthModule::registerMember(const std::string& username, const std::string& password,
                               const std::string& name, int age, const std::string& gender,
                               double height, double weight, const std::string& membershipType) {
    std::string hashedPassword = hashPassword(password);
    
    time_t now = time(0);
    std::tm* timeinfo = localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d");
    std::string currentDate = oss.str();
    
    // Calculate expiry date (1 year from now)
    time_t expiryTime = now + (365 * 24 * 60 * 60);
    timeinfo = localtime(&expiryTime);
    oss.str("");
    oss.clear();
    oss << std::put_time(timeinfo, "%Y-%m-%d");
    std::string expiryDate = oss.str();
    
    // First, insert into users table
    oss.str("");
    oss.clear();
    oss << std::put_time(localtime(&now), "%Y-%m-%d %H:%M:%S");
    std::string createdDate = oss.str();
    
    std::string userQuery = "INSERT INTO users (username, password, role, createdDate) VALUES ('" 
                           + username + "', '" + hashedPassword + "', " + std::to_string(MEMBER) 
                           + ", '" + createdDate + "');";
    
    if (!db.executeQuery(userQuery)) {
        std::cout << "Registration failed. Username may already exist." << std::endl;
        return false;
    }
    
    // Get the newly created user ID
    std::string selectQuery = "SELECT id FROM users WHERE username = '" + username + "' ORDER BY id DESC LIMIT 1;";
    sqlite3_stmt* stmt = db.prepareStatement(selectQuery);
    if (!stmt) {
        std::cout << "Error retrieving user ID." << std::endl;
        return false;
    }
    
    int userId = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userId = sqlite3_column_int(stmt, 0);
    }
    db.finalizeStatement(stmt);
    
    if (userId == -1) {
        std::cout << "Error: Could not create user record." << std::endl;
        return false;
    }
    
    // Now insert into members table
    std::ostringstream memberQuery;
    memberQuery << "INSERT INTO members (id, name, age, gender, height, weight, membershipType, joinDate, expiryDate) "
               << "VALUES (" << userId << ", '" << name << "', " << age << ", '" << gender 
               << "', " << height << ", " << weight << ", '" << membershipType 
               << "', '" << currentDate << "', '" << expiryDate << "');";
    
    if (!db.executeQuery(memberQuery.str())) {
        std::cout << "Member profile creation failed." << std::endl;
        return false;
    }
    
    std::cout << "Member " << name << " registered successfully!" << std::endl;
    return true;}
bool AuthModule::login(const std::string& username, const std::string& password) {
    std::string hashedPassword = hashPassword(password);
    
    std::string query = "SELECT id, role FROM users WHERE username = '" + username 
                       + "' AND password = '" + hashedPassword + "' AND active = 1;";
    
    sqlite3_stmt* stmt = db.prepareStatement(query);
    if (!stmt) return false;
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        currentUserId = sqlite3_column_int(stmt, 0);
        currentUserRole = (UserRole)sqlite3_column_int(stmt, 1);
        currentUsername = username;
        
        db.finalizeStatement(stmt);
        std::cout << "Login successful! Welcome " << username << std::endl;
        return true;
    }
    
    db.finalizeStatement(stmt);
    std::cout << "Invalid username or password." << std::endl;
    return false;
}

bool AuthModule::logout() {
    currentUserId = 0;
    currentUserRole = MEMBER;
    currentUsername = "";
    std::cout << "Logged out successfully." << std::endl;
    return true;
}

void AuthModule::displayLoginMenu() {
    std::string username, password;
    int roleChoice;
    std::cout << "\n=== LOGIN ===" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "Role (1=Member, 2=Trainer, 3=Admin): ";
    std::cin >> roleChoice;
    UserRole role = (UserRole)roleChoice;
    if (role < MEMBER || role > ADMIN) {
        std::cout << "Invalid role selection." << std::endl;
        return;
    }
    // Only allow login if role matches
    std::string hashedPassword = hashPassword(password);
    std::string query = "SELECT id, role FROM users WHERE username = '" + username 
                       + "' AND password = '" + hashedPassword + "' AND active = 1 AND role = " + std::to_string(role) + ";";
    sqlite3_stmt* stmt = db.prepareStatement(query);
    if (!stmt) {
        std::cout << "Login failed due to database error." << std::endl;
        return;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        currentUserId = sqlite3_column_int(stmt, 0);
        currentUserRole = (UserRole)sqlite3_column_int(stmt, 1);
        currentUsername = username;
        db.finalizeStatement(stmt);
        std::cout << "Login successful! Welcome " << username << std::endl;
    } else {
        db.finalizeStatement(stmt);
        std::cout << "Invalid username, password, or role." << std::endl;
    }
}

void AuthModule::displayRegistrationMenu() {
    std::string username, password, name, gender, membershipType;
    int roleChoice, age;
    double height, weight;
    
    std::cout << "\n=== REGISTRATION ===" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "Role (1=Member, 2=Trainer, 3=Admin): ";
    std::cin >> roleChoice;
    
    UserRole role = (UserRole)roleChoice;
    if (role < MEMBER || role > ADMIN) {
        std::cout << "Invalid role selection." << std::endl;
        return;
    }
    
    // If registering as a member, collect additional details
    if (role == MEMBER) {
        std::cout << "\n=== MEMBER DETAILS ===" << std::endl;
        std::cout << "Full Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Age: ";
        std::cin >> age;
        std::cout << "Gender (Male/Female): ";
        std::cin >> gender;
        std::cout << "Height (cm): ";
        std::cin >> height;
        std::cout << "Weight (kg): ";
        std::cin >> weight;
        std::cout << "Membership Type (Gold/Silver/Bronze): ";
        std::cin >> membershipType;
        
        registerMember(username, password, name, age, gender, height, weight, membershipType);
    } else {
        // For trainers and admins, just register as user
        registerUser(username, password, role);
    }
}
