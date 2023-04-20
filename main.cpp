#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>

int main() {
    std::ifstream bookDatabase;
    bookDatabase.open("GoodReads100kBooksModified.csv");
    std::string unusedStrings;

    std::map<std::string, std::string> tempMap;

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 5; j++) {
            getline(bookDatabase, unusedStrings, ',');
        }
        std::string title;
        std::string totalRatings;
        getline(bookDatabase, title, ',');
        getline(bookDatabase, totalRatings);
        tempMap[title] = totalRatings;
        // should turn each unique book into its own object, will be easier to work with
    }

    for (auto iter = tempMap.begin(); iter != tempMap.end(); iter++) {
        std::cout << "TITLE: " << iter->first << std::endl;
        std::cout << "RATINGS: " << iter->second << std::endl;
    }
}