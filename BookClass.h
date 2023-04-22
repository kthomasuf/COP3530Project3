#pragma once
#include <iostream>
#include <vector>

class BookClass {
private:
    std::string fullTitle;
    std::string numberOfReviews;
    int numberOfReviewsInt;
    std::vector<std::string> uniqueWordsVector;
    void uniqueWords(std::string title);
public:
    BookClass(std::string title, std::string totalRatings);
    std::vector<std::string> returnUniqueWords();
    int returnNumberOfReviews();
};
