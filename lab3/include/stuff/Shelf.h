#pragma once
#include <vector>
#include "Book.h"

class Shelf {
public:
    Shelf(int capacity);
    void addBookToShelf(Book& bookToAdd);
    void removeBookFromShelf(const std::string& titleToRemove);
    int getShelfCapacity() const;

private:
    std::vector<Book> booksOnShelf;
    int shelfCapacity;
};