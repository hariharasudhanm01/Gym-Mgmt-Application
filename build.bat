@echo off
REM ============================================
REM Gym Management System - Build Script
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
g++ -c main.cpp -o main.o -I. -std=c++17 -w
g++ -c src/DatabaseManager.cpp -o DatabaseManager.o -I. -std=c++17 -w
g++ -c src/AuthModule.cpp -o AuthModule.o -I. -std=c++17 -w
g++ -c src/MemberModule.cpp -o MemberModule.o -I. -std=c++17 -w
g++ -c src/HealthModule.cpp -o HealthModule.o -I. -std=c++17 -w
g++ -c src/StatisticsModule.cpp -o StatisticsModule.o -I. -std=c++17 -w
g++ -c src/WorkoutModule.cpp -o WorkoutModule.o -I. -std=c++17 -w
g++ -c src/ProgressModule.cpp -o ProgressModule.o -I. -std=c++17 -w
echo C++ files compiled successfully!

REM Step 3: Link all object files together
echo.
echo [3/3] Linking application...
g++ -o GymApp.exe main.o DatabaseManager.o AuthModule.o MemberModule.o HealthModule.o StatisticsModule.o WorkoutModule.o ProgressModule.o sqlite3.o -std=c++17
if errorlevel 1 (
    echo ERROR: Linking failed!
    exit /b 1
)
echo.
echo ============================================
echo SUCCESS: GymApp.exe created!
echo ============================================
echo.
echo Run: GymApp.exe
echo.
