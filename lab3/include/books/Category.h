#pragma once
#include <string>
#include <vector>
#include "Book.h"

class Category {
public:
    Category(const std::string& categoryName);
    void assignBookToCategory(Book& bookToAssign);
    void validateCategory();

private:
    std::string categoryDescription;
    std::vector<Book> booksInCategory;
};