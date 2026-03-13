# Gym Management System - Complete Console Application

## 📋 Project Overview

A professional-grade Gym Management System built in C++ with SQLite3, featuring comprehensive member management, health tracking, workout planning, and progress monitoring.

## ✨ Key Features

### 1. User Authentication System
- **Role-Based Access Control**
  - Members (viewed personal data only)
  - Trainers (manage members & create plans)
  - Administrators (full system control)
- Secure registration and login
- User session management

### 2. Member Management
- Add new members with personal information
- Update member profiles
- Delete (deactivate) members
- Search members by name
- View all members list
- Track membership types and expiry dates

### 3. Health & BMI Tracking
- Automatic BMI calculation (Weight/Height²)
- BMI Categories:
  - Underweight (BMI < 18.5)
  - Normal Weight (18.5 ≤ BMI < 25)
  - Overweight (25 ≤ BMI < 30)
  - Obese (BMI ≥ 30)
- Health record history
- Health data analytics

### 4. Workout Planning
- Create custom workout plans
- Add exercises with sets, reps, and descriptions
- Difficulty levels (Beginner, Intermediate, Advanced)
- Sample workout templates
- Assign plans to members
- Track exercise progress

### 5. Progress Tracking
- Record weight and measurements
- Track BMI changes over time
- Achievement logging
- Progress history analysis
- Weight change calculations
- Performance metrics

### 6. Gym Statistics
- Total member count
- Active members tracking
- Average BMI calculation
- Membership distribution (Gold/Silver/Bronze)
- BMI category distribution
- Real-time analytics dashboard

## 🎯 Project Structure

```
Gym Mgmt Application/
├── include/
│   ├── DatabaseManager.h       # SQLite database interface
│   ├── AuthModule.h             # User authentication
│   ├── MemberModule.h           # Member CRUD operations
│   ├── HealthModule.h           # Health & BMI tracking
│   ├── StatisticsModule.h       # Analytics & reporting
│   ├── WorkoutModule.h          # Workout planning
│   └── ProgressModule.h         # Progress tracking
│
├── src/
│   ├── DatabaseManager.cpp
│   ├── AuthModule.cpp
│   ├── MemberModule.cpp
│   ├── HealthModule.cpp
│   ├── StatisticsModule.cpp
│   ├── WorkoutModule.cpp
│   └── ProgressModule.cpp
│
├── libs/
│   └── sqlite/
│       ├── sqlite3.h            # SQLite header
│       └── sqlite3.c            # SQLite source
│
├── main.cpp                     # Application entry point
├── sqlite3_wrapper.cpp          # SQLite integration wrapper
├── demo.cpp                     # Feature demonstration
└── README.md                    # This file
```

## 🗄️ Database Schema

### Users Table
```sql
users (
  id INTEGER PRIMARY KEY,
  username TEXT UNIQUE NOT NULL,
  password TEXT NOT NULL,
  role INTEGER (1=Member, 2=Trainer, 3=Admin),
  createdDate TEXT,
  active INTEGER DEFAULT 1
)
```

### Members Table
```sql
members (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  age INTEGER,
  gender TEXT,
  height REAL,
  weight REAL,
  membershipType TEXT (Gold/Silver/Bronze),
  joinDate TEXT,
  expiryDate TEXT,
  active INTEGER DEFAULT 1
)
```

### Health Records Table
```sql
healthRecords (
  id INTEGER PRIMARY KEY,
  memberId INTEGER,
  height REAL,
  weight REAL,
  bmi REAL,
  category TEXT,
  recordDate TEXT,
  FOREIGN KEY(memberId) REFERENCES members(id)
)
```

### Workout Plans Table
```sql
workoutPlans (
  id INTEGER PRIMARY KEY,
  memberId INTEGER,
  planName TEXT NOT NULL,
  difficulty TEXT,
  createdDate TEXT,
  active INTEGER DEFAULT 1,
  FOREIGN KEY(memberId) REFERENCES members(id)
)
```

### Exercises Table
```sql
exercises (
  id INTEGER PRIMARY KEY,
  planId INTEGER,
  name TEXT NOT NULL,
  sets INTEGER,
  reps INTEGER,
  description TEXT,
  muscleGroup TEXT,
  FOREIGN KEY(planId) REFERENCES workoutPlans(id)
)
```

### Progress Records Table
```sql
progressRecords (
  id INTEGER PRIMARY KEY,
  memberId INTEGER,
  weight REAL,
  bmi REAL,
  achievement TEXT,
  recordDate TEXT,
  FOREIGN KEY(memberId) REFERENCES members(id)
)
```

## 👥 User Roles & Permissions

### Member (Role 1)
- View personal health data
- Track own progress
- View assigned workout plans
- Update personal information

### Trainer (Role 2)
- Manage all members
- Record health data
- Create workout plans
- Track member progress
- View gym statistics

### Administrator (Role 3)
- Full system control
- User management
- Member administration
- Health & statistics access
- System configuration

## 🚀 Compilation & Running

### Prerequisites
- GCC/G++ compiler (MinGW recommended for Windows)
- C++17 support

### Compile
```bash
g++ main.cpp src/*.cpp sqlite3_wrapper.cpp -o GymApp.exe \
    -I. -std=c++17 -fpermissive
```

### Run
```bash
./GymApp.exe
```

### View Demo
```bash
g++ demo.cpp -o GymDemo.exe && ./GymDemo.exe
```

## 📊 Sample Workflows

### Registering & Login
1. Select "Register New User" from main menu
2. Enter username, password, and role
3. Login with created credentials
4. Access role-specific dashboard

### Adding a Member
1. Login as Trainer or Admin
2. Navigate to "Member Management"
3. Select "Add New Member"
4. Enter personal information (name, age, height, weight, etc.)
5. Select membership type (Gold/Silver/Bronze)

### Recording Health Data
1. Go to "Health & BMI Management"
2. Enter member ID
3. Record height and weight
4. System calculates BMI and category automatically

### Creating Workout Plan
1. Navigate to "Workout Management"
2. Create plan (name and difficulty level)
3. Add exercises (name, sets, reps, muscle group)
4. Assign plan to members

### Tracking Progress
1. Access "Progress Tracking"
2. Record weight and achievements
3. View progress history
4. Analyze weight and BMI trends

## 🔧 Technical Features

- **Object-Oriented Design**: Modular class structure
- **Database Integration**: SQLite3 for persistence
- **Error Handling**: Comprehensive error messages
- **Date Management**: Current date/time tracking
- **Data Validation**: Input validation and constraints
- **Memory Management**: Smart pointers for resource handling
- **Flexible Queries**: Dynamic SQL generation
- **Role-Based Access**: Secure role validation

## 🐛 Known Limitations

- Passwords stored in plain text (use hashing in production)
- Single-threaded operation
- Console-based UI (no graphical interface)
- Local database storage only (no network support)

## 🚀 Future Enhancements

- Web-based GUI interface
- Password encryption and hashing
- Multi-user concurrent access
- Network/cloud database support
- Mobile app integration
- Email notifications
- Data export (PDF/Excel reports)
- Advanced analytics and charts
- Membership payment tracking
- Nutritional planning module

## 📝 Code Standards

- C++17 standard compliance
- Clear variable/function naming
- Inline documentation
- Error handling with try-catch patterns
- Resource cleanup with destructors
- Const correctness

## 💾 Database File

- Automatically created as `gym_management.db` on first run
- SQLite format, can be opened with any SQLite browser
- Schema automatically created on initialization

## 🔐 Security Note

This application is designed for demonstration purposes. For production use:
- Implement proper password hashing (bcrypt, argon2)
- Add SQL injection prevention
- Implement proper access control lists
- Add audit logging
- Encrypt sensitive data
- Use HTTPS for network deployment

## 📞 Support

For enhancement requests or bug reports, review the code structure and modify as needed.

---

**Version**: 1.0
**Created**: 2026-03-12
**Language**: C++17
**Database**: SQLite3
**Status**: Fully Functional ✓
