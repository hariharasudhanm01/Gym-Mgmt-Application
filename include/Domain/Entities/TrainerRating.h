#ifndef TRAINERRATING_H
#define TRAINERRATING_H

#include <string>

class TrainerRating {
private:
    int ratingId;
    int trainerId;
    int memberId;
    double ratingScore;
    std::string review;

public:
    TrainerRating() : ratingId(0), trainerId(0), memberId(0), ratingScore(0.0) {}
    
    TrainerRating(int rId, int tId, int mId, double score, const std::string& rev)
        : ratingId(rId), trainerId(tId), memberId(mId), ratingScore(score), review(rev) {}

    int getRatingId() const { return ratingId; }
    void setRatingId(int id) { ratingId = id; }

    int getTrainerId() const { return trainerId; }
    void setTrainerId(int id) { trainerId = id; }

    int getMemberId() const { return memberId; }
    void setMemberId(int id) { memberId = id; }

    double getRatingScore() const { return ratingScore; }
    void setRatingScore(double score) { ratingScore = score; }

    std::string getReview() const { return review; }
    void setReview(const std::string& rev) { review = rev; }
};

#endif
