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
    addUnwantedCharactersSet();
    addUnwantedWords();
    uniqueWords(fullTitle);
    uniqueGenres(allGenres);
}
void BookClass::addUnwantedCharactersSet() {
    notWantedCharacters.insert(' ');
    notWantedCharacters.insert('(');
    notWantedCharacters.insert(')');
    notWantedCharacters.insert('[');
    notWantedCharacters.insert(']');
    notWantedCharacters.insert('{');
    notWantedCharacters.insert('}');
    notWantedCharacters.insert(':');
    notWantedCharacters.insert(';');
    notWantedCharacters.insert('!');
    notWantedCharacters.insert('?');
    notWantedCharacters.insert('<');
    notWantedCharacters.insert('>');
    notWantedCharacters.insert('+');
    notWantedCharacters.insert('=');
}
void BookClass::addUnwantedWords() {
    notWantedWords.insert("");
    notWantedWords.insert("The");
    notWantedWords.insert("the");
    notWantedWords.insert("Of");
    notWantedWords.insert("of");
    notWantedWords.insert("To");
    notWantedWords.insert("to");
    notWantedWords.insert("Too");
    notWantedWords.insert("too");
    notWantedWords.insert("For");
    notWantedWords.insert("for");
    notWantedWords.insert("And");
    notWantedWords.insert("and");
    notWantedWords.insert("A");
    notWantedWords.insert("a");
    notWantedWords.insert("In");
    notWantedWords.insert("in");
    notWantedWords.insert("Be");
    notWantedWords.insert("be");
    notWantedWords.insert("On");
    notWantedWords.insert("on");
    notWantedWords.insert("With");
    notWantedWords.insert("with");
    notWantedWords.insert("At");
    notWantedWords.insert("at");
    notWantedWords.insert("By");
    notWantedWords.insert("by");
    notWantedWords.insert("From");
    notWantedWords.insert("from");
    notWantedWords.insert("Out");
    notWantedWords.insert("out");
    notWantedWords.insert("Into");
    notWantedWords.insert("into");
    notWantedWords.insert("Now");
    notWantedWords.insert("now");
    notWantedWords.insert("Over");
    notWantedWords.insert("over");
    notWantedWords.insert("After");
    notWantedWords.insert("after");
    notWantedWords.insert("But");
    notWantedWords.insert("but");
    notWantedWords.insert("About");
    notWantedWords.insert("about");
    notWantedWords.insert("Like");
    notWantedWords.insert("like");
    notWantedWords.insert("When");
    notWantedWords.insert("when");
    notWantedWords.insert("Then");
    notWantedWords.insert("then");
    notWantedWords.insert("Only");
    notWantedWords.insert("only");
    notWantedWords.insert("Also");
    notWantedWords.insert("also");
    notWantedWords.insert("How");
    notWantedWords.insert("how");
    notWantedWords.insert("Well");
    notWantedWords.insert("well");
    notWantedWords.insert("Most");
    notWantedWords.insert("most");
    notWantedWords.insert("Not");
    notWantedWords.insert("not");
}
void BookClass::uniqueWords(std::string title) {
    // Logic obtained from https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
    std::string uniqueWord;
    for (int i = 0; i < title.size(); i++) {
        if (notWantedCharacters.count(title[i]) == 1 || i == (title.size() - 1)) {
            if (i == (title.size() - 1)) {
                uniqueWord += title[i];
            }
            if (notWantedWords.count(uniqueWord) != 1) {
                uniqueWordsVector.push_back(uniqueWord);
            }
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