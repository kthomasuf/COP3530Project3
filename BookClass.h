#pragma once
#include <iostream>
#include <vector>
#include <set>

class BookClass {
private:
    std::string allGenres;
    std::string fullTitle;
    std::string numberOfReviews;
    int numberOfReviewsInt;
    std::vector<std::string> uniqueWordsVector;
    std::vector<std::string> uniqueGenresVector;
    std::set<std::string> genreSet;
    std::set<char> notWantedCharacters;
    std::set<std::string> notWantedWords;

    void addUnwantedCharactersSet();
    void addUnwantedWords();
    void uniqueWords(std::string title);
    void uniqueGenres(std::string genre);
public:
    BookClass(std::string genre, std::string title, std::string totalRatings);
    std::vector<std::string> returnUniqueWords();
    std::set<std::string> returnGenres();
    int returnNumberOfReviews();
};