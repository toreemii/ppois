#pragma once
#include "Book.h"
#include <vector>

class CatalogSystem {
public:
    void registerBook(Book& bookToRegister);
    void updateBookStatus(const std::string& title, bool isAvailable);
    std::vector<Book> getAllBooks() const;

private:
    std::vector<Book> catalogedBooks;
};