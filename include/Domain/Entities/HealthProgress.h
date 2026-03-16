#ifndef HEALTHPROGRESS_H
#define HEALTHPROGRESS_H

#include <string>

class HealthProgress {
private:
    int progressId;
    int memberId;
    double weight;
    double bodyFat;
    double muscleMass;
    std::string date;

public:
    HealthProgress() : progressId(0), memberId(0), weight(0.0), bodyFat(0.0), muscleMass(0.0) {}
    
    HealthProgress(int pId, int mId, double w, double bf, double mm, const std::string& d)
        : progressId(pId), memberId(mId), weight(w), bodyFat(bf), muscleMass(mm), date(d) {}

    int getProgressId() const { return progressId; }
    void setProgressId(int id) { progressId = id; }

    int getMemberId() const { return memberId; }
    void setMemberId(int id) { memberId = id; }

    double getWeight() const { return weight; }
    void setWeight(double w) { weight = w; }

    double getBodyFat() const { return bodyFat; }
    void setBodyFat(double bf) { bodyFat = bf; }

    double getMuscleMass() const { return muscleMass; }
    void setMuscleMass(double mm) { muscleMass = mm; }

    std::string getDate() const { return date; }
    void setDate(const std::string& d) { date = d; }
};

#endif
