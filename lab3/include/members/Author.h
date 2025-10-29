#pragma once
#include <string>
#include <vector>
#include "Book.h"

class Author {
public:
    Author(const std::string& fullName);
    void addWrittenBook(Book& bookToAdd);
    std::vector<Book> getWrittenBooks() const;

private:
    std::string authorFullName;
    std::vector<Book> writtenBooksList;
};