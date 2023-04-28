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
#include <chrono>

int main()
{
    std::ifstream bookDatabase;
    bookDatabase.open("cmake-build-debug/GoodReads100kBooksGenre.csv");
    std::string unusedStrings;
    getline(bookDatabase, unusedStrings);

    std::unordered_map<std::string, int> uniqueWordsMap;
    std::unordered_map<std::string, int> historyWordsMap;
    std::unordered_map<std::string, int> scienceWordsMap;
    std::unordered_map<std::string, int> fictionWordsMap;

    std::vector<BookClass> bookObjects;

    std::set<std::string> allGenres;
    for (int i = 0; i < 100001; i++)
    {
        getline(bookDatabase, unusedStrings, ',');
        std::string genre;
        getline(bookDatabase, genre, ',');
        for (int j = 0; j < 3; j++)
        {
            getline(bookDatabase, unusedStrings, ',');
        }
        std::string title;
        std::string totalRatings;
        getline(bookDatabase, title, ',');
        getline(bookDatabase, totalRatings);

        if (title == "")
        {
            break;
        }

        BookClass newBook(genre, title, totalRatings);
        bookObjects.push_back(newBook);

        std::vector<std::string> tempVector = newBook.returnUniqueWords();
        std::set<std::string> tempSet = newBook.returnGenres();

        for (int k = 0; k < tempVector.size(); k++)
        {
            uniqueWordsMap[tempVector[k]] += newBook.returnNumberOfReviews();

            if (tempSet.count("History") == 1)
            {
                historyWordsMap[tempVector[k]] += newBook.returnNumberOfReviews();
            }
            if (tempSet.count("Science") == 1)
            {
                scienceWordsMap[tempVector[k]] += newBook.returnNumberOfReviews();
            }
            if (tempSet.count("Fiction") == 1)
            {
                fictionWordsMap[tempVector[k]] += newBook.returnNumberOfReviews();
            }
        }

        std::set_union(allGenres.begin(), allGenres.end(), tempSet.begin(), tempSet.end(), std::inserter(allGenres, allGenres.begin()));
    }

    std::string userInput;
    while (userInput != "6")
    {
        std::cout << "What would you like to do? (Enter a number)" << std::endl;
        std::cout << "1. List Most Popular Keywords to Include in a Title" << std::endl;
        std::cout << "2. List Most Popular Keywords to Include in Title by Genre" << std::endl;
        std::cout << "3. List Least Popular Keywords to Include in a Title" << std::endl;
        std::cout << "4. List Least Popular Keywords to Include in Title by Genre" << std::endl;
        std::cout << "5. See all genres and what is the total amount of genres" << std::endl;
        std::cout << "6. Exit Program" << std::endl;
        std::cin >> userInput;
        if (userInput == "1")
        {
            std::cout << "Program will list the most popular words to include in title regardless of genre" << std::endl;

            // time starts here for heap
            auto begin = std::chrono::high_resolution_clock::now();

            MaxHeap newMaxHeap(uniqueWordsMap);
            std::pair<std::string, int> temp;
            for (int i = 1; i < 101; i++)
            {
                temp = newMaxHeap.extractMax();
                std::cout << i << ". " << temp.first << " " << temp.second << std::endl;
            }

            // time ends here for heap
            auto end = std::chrono::high_resolution_clock::now();
            // print clock values
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            std::cout << "Max Heap time taken: " << elapsed.count() << " nanoseconds " << std::endl;

            // time starts here
            begin = std::chrono::high_resolution_clock::now();

            /*

            B+ Code HERE

            */

            // time ends here
            end = std::chrono::high_resolution_clock::now();
            // print clock values
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            std::cout << "B+ tree time taken: " << elapsed.count() << " nanoseconds " << std::endl;
        }
        if (userInput == "2")
        {
            std::cout << "Please enter what genre you would like to sort by (and press enter):" << std::endl;
            std::string genreToSortBy;
            bool validGenre = false;
            while (!validGenre)
            {

                std::cin >> genreToSortBy;
                // time starts here
                auto begin = std::chrono::high_resolution_clock::now();
                if (allGenres.count(genreToSortBy) == 1)
                {
                    validGenre = true;
                    std::unordered_map<std::string, int> uniqueWordsMapForSpecificGenre;

                    // Go through the whole books vector and check if the genre is in the vector's genre
                    for (int i = 0; i < bookObjects.size(); i++)
                    {
                        // Check if the genre is in the vector's genre
                        std::set<std::string> tempSet = bookObjects[i].returnGenres();

                        if (tempSet.count(genreToSortBy) == 1)
                        {
                            // Get all of the unique words in the title
                            std::vector<std::string> tempVector = bookObjects[i].returnUniqueWords();

                            // Go through the map and add the number of reviews that correspond to each word
                            for (int j = 0; j < tempVector.size(); j++)
                            {
                                uniqueWordsMapForSpecificGenre[tempVector[j]] += bookObjects[i].returnNumberOfReviews();
                            }
                        }
                    }
                    MaxHeap newMaxHeap(uniqueWordsMapForSpecificGenre);
                    int top100 = 101;
                    if (newMaxHeap.size() < 101)
                    {
                        top100 = newMaxHeap.size() + 1;
                    }
                    std::pair<std::string, int> temp;
                    for (int i = 1; i < top100; i++)
                    {
                        temp = newMaxHeap.extractMax();
                        std::cout << i << ". " << temp.first << " " << temp.second << std::endl;
                    }
                    // time ends here
                    auto end = std::chrono::high_resolution_clock::now();
                    // print clock values
                    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                    std::cout << "Max Heap time taken: " << elapsed.count() << " nanoseconds " << std::endl;
                }
                else
                {
                    std::cout << "Not a valid genre, try again!" << std::endl;
                }
            }
        }
        if (userInput == "3")
        {
            std::cout << "Program will list the least popular words to include in title regardless of genre" << std::endl;
            // time starts here
            auto begin = std::chrono::high_resolution_clock::now();

            MinHeap newMinHeap(uniqueWordsMap);
            std::pair<std::string, int> temp;
            // time starts here for heap
            for (int i = 1; i < 101; i++)
            {
                temp = newMinHeap.extractMin();
                std::cout << i << ". " << temp.first << " " << temp.second << std::endl;
            }
            // time ends here
            auto end = std::chrono::high_resolution_clock::now();
            // print clock values
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            std::cout << "Min Heap time taken: " << elapsed.count() << " nanoseconds " << std::endl;

            // time starts here
            begin = std::chrono::high_resolution_clock::now();

            /*

            B+ Code HERE

            */

            // time ends here
            end = std::chrono::high_resolution_clock::now();
            // print clock values
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            std::cout << "B+ Tree time taken: " << elapsed.count() << " nanoseconds " << std::endl;
        }
        if (userInput == "4")
        {
            std::cout << "Please enter what genre you would like to sort by (and press enter):" << std::endl;
            std::string genreToSortBy;
            bool validGenre = false;
            while (!validGenre)
            {
                std::cin >> genreToSortBy;
                // time starts here
                auto begin = std::chrono::high_resolution_clock::now();
                if (allGenres.count(genreToSortBy) == 1)
                {
                    validGenre = true;
                    std::unordered_map<std::string, int> uniqueWordsMapForSpecificGenre;

                    // Go through the whole books vector and check if the genre is in the vector's genre
                    for (int i = 0; i < bookObjects.size(); i++)
                    {
                        // Check if the genre is in the vector's genre
                        std::set<std::string> tempSet = bookObjects[i].returnGenres();

                        if (tempSet.count(genreToSortBy) == 1)
                        {
                            // Get all of the unique words in the title
                            std::vector<std::string> tempVector = bookObjects[i].returnUniqueWords();

                            // Go through the map and add the number of reviews that correspond to each word
                            for (int j = 0; j < tempVector.size(); j++)
                            {
                                uniqueWordsMapForSpecificGenre[tempVector[j]] += bookObjects[i].returnNumberOfReviews();
                            }
                        }
                    }
                    MinHeap newMinHeap(uniqueWordsMapForSpecificGenre);
                    int top100 = 101;
                    if (newMinHeap.size() < 101)
                    {
                        top100 = newMinHeap.size() + 1;
                    }
                    std::pair<std::string, int> temp;
                    for (int i = 1; i < top100; i++)
                    {
                        temp = newMinHeap.extractMin();
                        std::cout << i << ". " << temp.first << " " << temp.second << std::endl;
                    }
                    // time ends here
                    auto end = std::chrono::high_resolution_clock::now();
                    // print clock values
                    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                    std::cout << "Min Heap time taken: " << elapsed.count() << " nanoseconds " << std::endl;
                }
                else
                {
                    std::cout << "Not a valid genre, try again!" << std::endl;
                }
            }
        }
        if (userInput == "5")
        {
            // time starts here
            auto begin = std::chrono::high_resolution_clock::now();
            std::cout << "total amount of genres in the set of genres is " << allGenres.size() << std::endl;
            for (const std::string &str : allGenres)
            {
                std::cout << str << std::endl;
            }
            // time ends here
            auto end = std::chrono::high_resolution_clock::now();
            // print clock values
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            std::cout << "Min Heap time taken: " << elapsed.count() << " nanoseconds " << std::endl;
        }
    }

    return 0;
}