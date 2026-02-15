#pragma once
#include <string>
#include <vector>
#include "Book.h"

class Genre {
public:
    Genre(const std::string& genreName);
    void addBookToGenre(Book& bookToAdd);
    void listBooksInGenre();

private:
    std::string genreDescription;
    std::vector<Book> booksInGenre;
};