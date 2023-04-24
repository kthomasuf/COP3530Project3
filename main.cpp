#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iterator>
#include "BookClass.h"
#include "MaxHeap.h"
#include "MinHeap.h"

int main() {
    std::ifstream bookDatabase;
    bookDatabase.open("GoodReads100kBooksGenre.csv");
    std::string unusedStrings;
    getline(bookDatabase, unusedStrings);

    std::unordered_map<std::string, int> uniqueWordsMap;
    std::unordered_map<std::string, int> historyWordsMap;
    std::unordered_map<std::string, int> scienceWordsMap;
    std::unordered_map<std::string, int> fictionWordsMap;

    std::vector<BookClass> bookObjects;

    for (int i = 0; i < 100001; i++) {
        getline(bookDatabase, unusedStrings, ',');
        std::string genre;
        getline(bookDatabase, genre, ',');
        for (int j = 0; j < 3; j++) {
            getline(bookDatabase, unusedStrings, ',');
        }
        std::string title;
        std::string totalRatings;
        getline(bookDatabase, title, ',');
        getline(bookDatabase, totalRatings);

        BookClass newBook(genre, title, totalRatings);

        if (title == "") {
            break;
        }

        std::vector<std::string> tempVector = newBook.returnUniqueWords();
        std::set<std::string> tempSet = newBook.returnGenres();

        for (int k = 0; k < tempVector.size(); k++) {
            uniqueWordsMap[tempVector[k]] += newBook.returnNumberOfReviews();

            if (tempSet.count("History") == 1) {
                historyWordsMap[tempVector[k]] += newBook.returnNumberOfReviews();
            }
            if (tempSet.count("Science") == 1) {
                scienceWordsMap[tempVector[k]] += newBook.returnNumberOfReviews();
            }
            if (tempSet.count("Fiction") == 1) {
                fictionWordsMap[tempVector[k]] += newBook.returnNumberOfReviews();
            }
        }
    }
}