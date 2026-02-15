#include "Book.h"
#include <iostream>

Book::Book(const std::string& title, const std::string& authorName, int pageCount)
    : Publication(title, authorName), totalPagesCount(pageCount), bookmarkedPageNumber(0) {}

void Book::openToPage(int pageNumber) {
    if (pageNumber > 0 && pageNumber <= totalPagesCount) {
        std::cout << "Открыто на странице " << pageNumber << std::endl;
    }
}

void Book::bookmarkPage(int pageNumber) {
    if (pageNumber > 0 && pageNumber <= totalPagesCount) {
        bookmarkedPageNumber = pageNumber;
    }
}