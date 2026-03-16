@echo off
REM ============================================
REM Gym Management System (Clean Architecture) - Build Script
REM Windows Batch File for MinGW/GCC
REM ============================================

echo.
echo Building Gym Management Application...
echo.

REM Step 1: Compile SQLite3 as pure C code
echo [1/3] Compiling SQLite3 library...
gcc -c libs/sqlite/sqlite3.c -o sqlite3.o -w -DWIN32 -D_WIN32_WINNT=0x0600 -DSQLITE_OS_WIN=1 -DHAVE_USLEEP -DSQLITE_WIN32_GETVERSIONEX=0
if errorlevel 1 (
    echo ERROR: Failed to compile SQLite3
    exit /b 1
)
echo SQLite3 compiled successfully!

REM Step 2: Compile all C++ source files to object files
echo.
echo [2/3] Compiling C++ source files...

g++ -c src/Infrastructure/Database/DatabaseManager.cpp -o DatabaseManager.o -I. -std=c++17 -w
g++ -c src/Infrastructure/Repositories/UserRepository.cpp -o UserRepository.o -I. -std=c++17 -w
g++ -c src/Infrastructure/Repositories/MemberRepository.cpp -o MemberRepository.o -I. -std=c++17 -w
g++ -c src/Infrastructure/Repositories/TrainerRepository.cpp -o TrainerRepository.o -I. -std=c++17 -w
g++ -c src/Infrastructure/Repositories/RatingRepository.cpp -o RatingRepository.o -I. -std=c++17 -w
g++ -c src/Infrastructure/Repositories/WorkoutRepository.cpp -o WorkoutRepository.o -I. -std=c++17 -w
g++ -c src/Infrastructure/Repositories/ProgressRepository.cpp -o ProgressRepository.o -I. -std=c++17 -w

g++ -c src/Application/Services/AuthService.cpp -o AuthService.o -I. -std=c++17 -w
g++ -c src/Application/Services/MemberService.cpp -o MemberService.o -I. -std=c++17 -w
g++ -c src/Application/Services/TrainerService.cpp -o TrainerService.o -I. -std=c++17 -w
g++ -c src/Application/Services/AdminService.cpp -o AdminService.o -I. -std=c++17 -w

g++ -c src/Presentation/Menus/MainMenu.cpp -o MainMenu.o -I. -std=c++17 -w
g++ -c src/Presentation/Menus/AdminMenu.cpp -o AdminMenu.o -I. -std=c++17 -w
g++ -c src/Presentation/Menus/TrainerMenu.cpp -o TrainerMenu.o -I. -std=c++17 -w
g++ -c src/Presentation/Menus/MemberMenu.cpp -o MemberMenu.o -I. -std=c++17 -w

g++ -c main.cpp -o main.o -I. -std=c++17 -w

if errorlevel 1 (
    echo ERROR: Failed to compile C++ files
    exit /b 1
)
echo C++ files compiled successfully!

REM Step 3: Link all object files together
echo.
echo [3/3] Linking application...
g++ -o GymApp.exe main.o DatabaseManager.o UserRepository.o MemberRepository.o TrainerRepository.o RatingRepository.o WorkoutRepository.o ProgressRepository.o AuthService.o MemberService.o TrainerService.o AdminService.o MainMenu.o AdminMenu.o TrainerMenu.o MemberMenu.o sqlite3.o -std=c++17
if errorlevel 1 (
    echo ERROR: Linking failed!
    exit /b 1
)
echo.
echo ============================================
echo SUCCESS: GymApp.exe created!
echo ============================================
echo.
