#pragma once
#include "Book.h"
#include <vector>
#include <string>

class SearchService {
public:
    void indexBook(Book& bookToIndex);
    std::vector<Book> searchByTitle(const std::string& titleQuery) const;
    std::vector<Book> searchByAuthor(const std::string& authorQuery) const;

private:
    std::vector<Book> indexedBooks;
};