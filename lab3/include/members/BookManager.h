#pragma once
#include <vector>
#include "Book.h"

class BookManager {
public:
    void addBookToCollection(Book& bookToAdd);
    void removeBookFromCollection(const std::string& titleToRemove);
    Book findBookByTitle(const std::string& titleToFind) const;

private:
    std::vector<Book> managedBooksCollection;
};