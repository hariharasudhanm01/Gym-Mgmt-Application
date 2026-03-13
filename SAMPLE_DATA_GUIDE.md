# GYM MANAGEMENT SYSTEM - SETUP & SAMPLE DATA GUIDE

## ✅ Sample Setup Completed!

A setup program has been created (`Setup.exe`) to populate your database with sample data.

---

## 📊 SAMPLE DATA INCLUDED

### 3 Sample Trainers Created:

| Username | Password | Role |
|----------|----------|------|
| sarah_trainer | trainer123 | Trainer |
| mike_trainer | trainer456 | Trainer |
| alex_trainer | trainer789 | Trainer |

### 1 Sample Admin Created:

| Username | Password | Role |
|----------|----------|------|
| admin_user | admin123 | Admin |

### 10 Sample Members Created (with health data):

| # | Name | Age | Gender | Height | Weight | Membership |
|---|------|-----|--------|--------|--------|-----------|
| 1 | John Doe | 25 | Male | 175 cm | 75 kg | Gold |
| 2 | Sarah Johnson | 28 | Female | 162 cm | 58 kg | Gold |
| 3 | Michael Brown | 35 | Male | 180 cm | 85 kg | Silver |
| 4 | Emily Davis | 22 | Female | 168 cm | 62 kg | Gold |
| 5 | David Wilson | 45 | Male | 178 cm | 92 kg | Bronze |
| 6 | Jessica Martinez | 30 | Female | 165 cm | 70 kg | Silver |
| 7 | James Anderson | 32 | Male | 182 cm | 88 kg | Gold |
| 8 | Amanda Taylor | 26 | Female | 160 cm | 55 kg | Gold |
| 9 | Christopher Lee | 40 | Male | 176 cm | 95 kg | Silver |
| 10 | Nicole White | 29 | Female | 170 cm | 65 kg | Gold |

---

## 🚀 HOW TO USE

### Step 1: Run Setup Program (One-time setup)

```powershell
cd "c:\Users\hrm.ESKO-GRAPHICS\Desktop\Gym Mgmt Application"
.\Setup.exe
```

**Note:** Run this once to populate the database with sample data. The database will be created automatically with:
- All 10 members loaded
- Health records for each member
- Trainer accounts ready to use
- Admin account ready to use

### Step 2: Run the Main Application

```powershell
.\GymApp.exe
```

---

## 📝 LOGIN INSTRUCTIONS

### For Administrators

```
Username: admin_user
Password: admin123
```

**Admin Dashboard Access:**
- Member Management (add, update, delete, search)
- Health Management (record & track BMI)
- Workout Management (create plans, assign exercises)
- Progress Tracking (view member progress)
- View Statistics (gym analytics)

### For Trainers

Use any trainer account:
```
Username: sarah_trainer  | Password: trainer123
Username: mike_trainer   | Password: trainer456
Username: alex_trainer   | Password: trainer789
```

**Trainer Dashboard Access:**
- Manage Members (full CRUD operations)
- Record Health Data (BMI tracking)
- Create Workout Plans
- View Member Progress
- View Gym Statistics

---

## 🧪 TEST WORKFLOWS

### Test 1: View All Members
1. Run `.\GymApp.exe`
2. Login as `admin_user` / `admin123`
3. Select "Member Management"
4. Choose "View All Members"
5. ✓ See all 10 sample members listed with their details

### Test 2: Update a Member
1. In Member Management, select "Update Member"
2. Enter member ID (1-10)
3. Update any information
4. ✓ Changes are saved to database

### Test 3: Delete a Member
1. In Member Management, select "Delete Member"
2. Enter member ID
3. Confirm deletion
4. ✓ Member is deactivated (soft delete)

### Test 4: View Gym Statistics
1. From Admin/Trainer Dashboard, select "View Statistics"
2. ✓ See:
   - Total members (10)
   - Active members
   - Average BMI
   - Member distribution by type
   - BMI category distribution

### Test 5: Health Tracking
1. In Health Management, select "Record Health"
2. Enter member ID and new measurements
3. ✓ Health records are saved with BMI calculation

### Test 6: Workout Planning
1. In Workout Management, select "Create Workout Plan"
2. Assign plan to a member
3. Add exercises
4. ✓ Plan is saved and associated with member

---

## 📁 FILES PROVIDED

```
GymApp.exe              ← Main application (Run this!)
Setup.exe               ← Setup program (Run once to load sample data)
gym_management.db       ← Database file (auto-created, don't delete unless resetting)
README.md               ← Full project documentation
BUILD_GUIDE.md          ← Build instructions
COMPILATION_FIX.md      ← Technical documentation
SAMPLE_DATA_GUIDE.md    ← This file
```

---

## ⚙️ RESETTING THE DATABASE

If you want to start fresh:

```powershell
# Option 1: Delete database and re-run setup
Remove-Item gym_management.db
.\Setup.exe

# Option 2: Delete database and let app recreate it (empty)
Remove-Item gym_management.db
.\GymApp.exe
```

---

## 🎯 SAMPLE DATA FEATURES

Each sample member includes:

✅ **Profile Information**
- Realistic names, ages, genders
- Varied heights and weights
- Different membership types (Gold/Silver/Bronze)

✅ **Health Records**
- Initial health data with height/weight
- BMI automatically calculated
- Proper BMI categories assigned

✅ **Membership Details**
- Gold members: 12-month validity
- Silver members: 6-month validity  
- Bronze members: 3-month validity
- Expiry dates calculated from join date

✅ **Realistic Data**
- Age range: 22-45 years
- Height range: 160-182 cm
- Weight range: 55-95 kg
- Mix of different body types

---

## 💡 TESTING SCENARIOS

### Scenario 1: Gym Management
```
Login as admin_user
→ View all members (10 listed)
→ Check statistics (10 members total)
→ View BMI distribution
```

### Scenario 2: Health Tracking
```
Login as sarah_trainer
→ Update John Doe's health data
→ Record new weight (e.g., 73 kg)
→ View BMI change (should update)
→ Check member progress
```

### Scenario 3: Membership Management
```
Login as admin_user
→ Update Emily Davis's membership (change from Gold to Silver)
→ Update her weight
→ View updated expiry date
→ Verify changes in member list
```

### Scenario 4: Workout Assignment
```
Login as mike_trainer
→ Create new workout plan for James Anderson
→ Add sample exercises (bench press, squats, etc.)
→ Assign different difficulties
→ View member's workout plans
```

---

## 📊 STATISTICS YOU CAN VERIFY

After loading sample data:

**Expected Stats:**
- **Total Members:** 10
- **Gold Members:** 6 (John, Sarah, Emily, James, Amanda, Nicole)
- **Silver Members:** 3 (Michael, Jessica, Christopher)
- **Bronze Members:** 1 (David)
- **Average Weight:** ~71 kg
- **Average Height:** ~171 cm
- **Gender Split:** 5 Male, 5 Female

**BMI Categories:**
- Underweight: Emily Davis (BMI ~21.9)
- Normal Weight: Most members
- Overweight: Christopher Lee, David Wilson
- Can add more to test Obese category

---

## ✨ QUICK START GUIDE

### For First-Time Users:

1. **Download & Extract** - All files in: `C:\Users\hrm.ESKO-GRAPHICS\Desktop\Gym Mgmt Application`

2. **Run Setup** (one-time):
   ```powershell
   .\Setup.exe
   ```
   Wait for completion message.

3. **Run Application**:
   ```powershell
   .\GymApp.exe
   ```

4. **Login** with test account:
   ```
   Username: admin_user
   Password: admin123
   ```

5. **Explore Features**:
   - View members
   - Check statistics
   - Update/delete members
   - Track health
   - Create workout plans

---

## 🐛 TROUBLESHOOTING

**Problem:** Database not created after running Setup.exe

**Solution 1:** Run setup again:
```powershell
.\Setup.exe
```

**Solution 2:** Check file permissions in folder

**Solution 3:** Delete old database and restart:
```powershell
Remove-Item gym_management.db
.\Setup.exe
```

---

**Version:** 1.0  
**Date Created:** March 12, 2026  
**Status:** ✅ Ready to Use  
**Sample Members:** 10  
**Sample Trainers:** 3  
**Sample Admin:** 1  
