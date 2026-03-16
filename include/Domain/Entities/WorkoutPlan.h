#ifndef WORKOUTPLAN_H
#define WORKOUTPLAN_H

#include <string>

class WorkoutPlan {
private:
    int planId;
    int memberId;
    int trainerId;
    std::string exerciseList;
    int durationWeeks;
    std::string difficultyLevel;

public:
    WorkoutPlan() : planId(0), memberId(0), trainerId(0), durationWeeks(0) {}
    
    WorkoutPlan(int pId, int mId, int tId, const std::string& exercises, int weeks, const std::string& diff)
        : planId(pId), memberId(mId), trainerId(tId), exerciseList(exercises), durationWeeks(weeks), difficultyLevel(diff) {}

    int getPlanId() const { return planId; }
    void setPlanId(int id) { planId = id; }

    int getMemberId() const { return memberId; }
    void setMemberId(int id) { memberId = id; }

    int getTrainerId() const { return trainerId; }
    void setTrainerId(int id) { trainerId = id; }

    std::string getExerciseList() const { return exerciseList; }
    void setExerciseList(const std::string& exercises) { exerciseList = exercises; }

    int getDurationWeeks() const { return durationWeeks; }
    void setDurationWeeks(int weeks) { durationWeeks = weeks; }

    std::string getDifficultyLevel() const { return difficultyLevel; }
    void setDifficultyLevel(const std::string& diff) { difficultyLevel = diff; }
};

#endif
