# Gym Management System - Build Script (PowerShell)
# For Windows with MinGW/GCC

Write-Host "========================================"
Write-Host "Building Gym Management Application"
Write-Host "========================================"
Write-Host ""

# Step 1: Compile SQLite3 as C code
Write-Host "[1/3] Compiling SQLite3 library..." -ForegroundColor Cyan
gcc -c libs/sqlite/sqlite3.c -o sqlite3.o -w -DWIN32 -D_WIN32_WINNT=0x0600 -DSQLITE_OS_WIN=1 -DHAVE_USLEEP -DSQLITE_WIN32_GETVERSIONEX=0
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: Failed to compile SQLite3" -ForegroundColor Red
    exit 1
}
Write-Host "✓ SQLite3 compiled successfully!" -ForegroundColor Green
Write-Host ""

# Step 2: Compile C++ source files
Write-Host "[2/3] Compiling C++ source files..." -ForegroundColor Cyan
$cppFiles = @(
    "main.cpp",
    "src/DatabaseManager.cpp",
    "src/AuthModule.cpp",
    "src/MemberModule.cpp",
    "src/HealthModule.cpp",
    "src/StatisticsModule.cpp",
    "src/WorkoutModule.cpp",
    "src/ProgressModule.cpp"
)

foreach ($cppFile in $cppFiles) {
    $objFile = $cppFile -replace "\.cpp$", ".o"
    Write-Host "  Compiling $cppFile..." -ForegroundColor Gray
    & g++ -c $cppFile -o $objFile -I. -std=c++17 -w
    if ($LASTEXITCODE -ne 0) {
        Write-Host "ERROR: Failed to compile $cppFile" -ForegroundColor Red
        exit 1
    }
}
Write-Host "✓ C++ files compiled successfully!" -ForegroundColor Green
Write-Host ""

# Step 3: Link all object files
Write-Host "[3/3] Linking application..." -ForegroundColor Cyan
& g++ -o GymApp.exe main.o DatabaseManager.o AuthModule.o MemberModule.o HealthModule.o StatisticsModule.o WorkoutModule.o ProgressModule.o sqlite3.o -std=c++17
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: Linking failed!" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "SUCCESS: GymApp.exe created!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""
Write-Host "To run the application:" -ForegroundColor Cyan
Write-Host "  .\GymApp.exe" -ForegroundColor Yellow
Write-Host ""
