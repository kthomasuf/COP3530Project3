#include "BookClass.h"
#include <iostream>
#include <string>
#include <vector>

BookClass::BookClass(std::string title, std::string totalReviews) {
    this->fullTitle = title;
    this->numberOfReviews = totalReviews;
    if (totalReviews == "") {
        this->numberOfReviewsInt = 0;
    }
    else {
        this->numberOfReviewsInt = std::stoi(totalReviews);
    }
    uniqueWords(fullTitle);
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
std::vector<std::string> BookClass::returnUniqueWords() {
    return uniqueWordsVector;
}
int BookClass::returnNumberOfReviews() {
    return numberOfReviewsInt;
}