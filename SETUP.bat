@echo off
REM Gym Management System - Setup Batch File
REM This sets up the database with 10 sample members and test accounts

echo.
echo.
echo ========================================
echo GYM MANAGEMENT SYSTEM SETUP
echo ========================================
echo.
echo This will create a database with:
echo   - 10 sample members with health data
echo   - 3 trainer accounts
echo   - 1 admin account
echo.

if exist gym_management.db (
    echo WARNING: Database already exists!
    echo Existing data will be overwritten.
    echo.
    set /p choice="Continue? (y/n): "
    if /i not "!choice!"=="y" (
        echo Setup cancelled.
        pause
        exit /b
    )
    del /q gym_management.db
)

echo.
echo Running setup...
.\Setup.exe

echo.
echo ========================================
echo SETUP COMPLETE!
echo ========================================
echo.
echo You can now run: GymApp.exe
echo.
echo Test Login Credentials:
echo.
echo ADMIN:
echo   Username: admin_user
echo   Password: admin123
echo.
echo TRAINERS:
echo   Username: sarah_trainer  | Password: trainer123
echo   Username: mike_trainer   | Password: trainer456
echo   Username: alex_trainer   | Password: trainer789
echo.

pause
