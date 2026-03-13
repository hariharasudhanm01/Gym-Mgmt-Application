Write-Host "========================================"
Write-Host "Building Gym Management Application"
Write-Host "========================================"
Write-Host ""

Write-Host "[1/3] Compiling SQLite3 library..." -ForegroundColor Cyan
gcc -c libs/sqlite/sqlite3.c -o sqlite3.o -w -DWIN32 -D_WIN32_WINNT=0x0600 -DSQLITE_OS_WIN=1 -DHAVE_USLEEP -DSQLITE_WIN32_GETVERSIONEX=0

if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: Failed to compile SQLite3" -ForegroundColor Red
    exit 1
}
Write-Host "SQLite3 compiled successfully!" -ForegroundColor Green
Write-Host ""

Write-Host "[2/3] Compiling C++ source files..." -ForegroundColor Cyan
g++ -c main.cpp -o main.o -I. -std=c++17 -w
g++ -c src/DatabaseManager.cpp -o DatabaseManager.o -I. -std=c++17 -w
g++ -c src/AuthModule.cpp -o AuthModule.o -I. -std=c++17 -w
g++ -c src/MemberModule.cpp -o MemberModule.o -I. -std=c++17 -w
g++ -c src/HealthModule.cpp -o HealthModule.o -I. -std=c++17 -w
g++ -c src/StatisticsModule.cpp -o StatisticsModule.o -I. -std=c++17 -w
g++ -c src/WorkoutModule.cpp -o WorkoutModule.o -I. -std=c++17 -w
g++ -c src/ProgressModule.cpp -o ProgressModule.o -I. -std=c++17 -w

Write-Host "C++ files compiled successfully!" -ForegroundColor Green
Write-Host ""

Write-Host "[3/3] Linking application..." -ForegroundColor Cyan
g++ -o GymApp.exe main.o DatabaseManager.o AuthModule.o MemberModule.o HealthModule.o StatisticsModule.o WorkoutModule.o ProgressModule.o sqlite3.o -std=c++17

if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: Linking failed!" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "SUCCESS: GymApp.exe created!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""
Write-Host "Run: .\GymApp.exe" -ForegroundColor Cyan
Write-Host ""
