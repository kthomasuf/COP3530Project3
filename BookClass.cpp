#include "BookClass.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>

BookClass::BookClass(std::string genre, std::string title, std::string totalReviews) {
    this->allGenres = genre;
    this->fullTitle = title;
    this->numberOfReviews = totalReviews;
    if (totalReviews == "") {
        this->numberOfReviewsInt = 0;
    }
    else {
        this->numberOfReviewsInt = std::stoi(totalReviews);
    }
    uniqueWords(fullTitle);
    uniqueGenres(allGenres);
}
void BookClass::uniqueWords(std::string title) {
    // Logic obtained from https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
    std::string uniqueWord;
    for (int i = 0; i < title.size(); i++) {
        if (title[i] == ' ' || i == (title.size() - 1)) {
            if (i == (title.size() - 1)) {
                uniqueWord += title[i];
            }
            uniqueWordsVector.push_back(uniqueWord);
            uniqueWord = "";
        }
        else {
            uniqueWord += title[i];
        }
    }
}
void BookClass::uniqueGenres(std::string genre) {
    // Logic obtained from https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
    std::string uniqueGenre;
    for (int i = 0; i < genre.size(); i++) {
        if (genre[i] == ' ' || i == (genre.size() - 1)) {
            if (i == (genre.size() - 1)) {
                uniqueGenre += genre[i];
            }
            genreSet.insert(uniqueGenre);
            uniqueGenre = "";
        }
        else {
            uniqueGenre += genre[i];
        }
    }
}
std::vector<std::string> BookClass::returnUniqueWords() {
    return uniqueWordsVector;
}
std::set<std::string> BookClass::returnGenres() {
    return genreSet;
}
int BookClass::returnNumberOfReviews() {
    return numberOfReviewsInt;
}