#include "../../../include/Infrastructure/Repositories/RatingRepository.h"
#include "../../../include/Infrastructure/Database/DatabaseManager.h"

TrainerRating RatingRepository::getById(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT rating_id, trainer_id, member_id, rating_score, review FROM TrainerRatings WHERE rating_id = " + std::to_string(id);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    TrainerRating rating;
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        rating.setRatingId(sqlite3_column_int(stmt, 0));
        rating.setTrainerId(sqlite3_column_int(stmt, 1));
        rating.setMemberId(sqlite3_column_int(stmt, 2));
        rating.setRatingScore(sqlite3_column_double(stmt, 3));
        if(sqlite3_column_text(stmt, 4)) rating.setReview(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    }
    db->finalizeStatement(stmt);
    return rating;
}

std::vector<TrainerRating> RatingRepository::getAll() {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT rating_id, trainer_id, member_id, rating_score, review FROM TrainerRatings";
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<TrainerRating> ratings;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        TrainerRating rating;
        rating.setRatingId(sqlite3_column_int(stmt, 0));
        rating.setTrainerId(sqlite3_column_int(stmt, 1));
        rating.setMemberId(sqlite3_column_int(stmt, 2));
        rating.setRatingScore(sqlite3_column_double(stmt, 3));
        if(sqlite3_column_text(stmt, 4)) rating.setReview(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        ratings.push_back(rating);
    }
    db->finalizeStatement(stmt);
    return ratings;
}

std::vector<TrainerRating> RatingRepository::getByTrainerId(int trainerId) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "SELECT rating_id, trainer_id, member_id, rating_score, review FROM TrainerRatings WHERE trainer_id = " + std::to_string(trainerId);
    sqlite3_stmt* stmt = db->prepareStatement(query);
    
    std::vector<TrainerRating> ratings;
    while (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        TrainerRating rating;
        rating.setRatingId(sqlite3_column_int(stmt, 0));
        rating.setTrainerId(sqlite3_column_int(stmt, 1));
        rating.setMemberId(sqlite3_column_int(stmt, 2));
        rating.setRatingScore(sqlite3_column_double(stmt, 3));
        if(sqlite3_column_text(stmt, 4)) rating.setReview(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        ratings.push_back(rating);
    }
    db->finalizeStatement(stmt);
    return ratings;
}

bool RatingRepository::add(const TrainerRating& rating) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "INSERT INTO TrainerRatings (trainer_id, member_id, rating_score, review) VALUES (" +
                        std::to_string(rating.getTrainerId()) + ", " +
                        std::to_string(rating.getMemberId()) + ", " +
                        std::to_string(rating.getRatingScore()) + ", '" +
                        rating.getReview() + "')";
    return db->executeQuery(query);
}

bool RatingRepository::update(const TrainerRating& rating) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "UPDATE TrainerRatings SET "
                        "trainer_id = " + std::to_string(rating.getTrainerId()) + ", "
                        "member_id = " + std::to_string(rating.getMemberId()) + ", "
                        "rating_score = " + std::to_string(rating.getRatingScore()) + ", "
                        "review = '" + rating.getReview() + "' "
                        "WHERE rating_id = " + std::to_string(rating.getRatingId());
    return db->executeQuery(query);
}

bool RatingRepository::remove(int id) {
    DatabaseManager* db = DatabaseManager::getInstance();
    std::string query = "DELETE FROM TrainerRatings WHERE rating_id = " + std::to_string(id);
    return db->executeQuery(query);
}
