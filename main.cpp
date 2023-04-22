#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iterator>
#include "BookClass.h"

int main() {
    std::ifstream bookDatabase;
    bookDatabase.open("GoodReads100kBooksFinal.csv");
    std::string unusedStrings;
    getline(bookDatabase, unusedStrings);

    std::unordered_map<std::string, int> uniqueWordsMap;
    std::vector<BookClass> bookObjects;

    for (int i = 0; i < 100001; i++) {
        for (int j = 0; j < 5; j++) {
            getline(bookDatabase, unusedStrings, ',');
        }
        std::string title;
        std::string totalRatings;
        getline(bookDatabase, title, ',');
        getline(bookDatabase, totalRatings);
        BookClass newBook(title, totalRatings);

        if (title == "") {
            break;
        }

        std::vector<std::string> tempVector = newBook.returnUniqueWords();

        for (int k = 0; k < tempVector.size(); k++) {
            uniqueWordsMap[tempVector[k]] += newBook.returnNumberOfReviews();
        }
    }
}