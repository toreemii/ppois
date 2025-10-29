#pragma once
#include "Publication.h"
#include <string>

class Book : public Publication {
public:
    Book(const std::string& title, const std::string& authorName, int pageCount);
    void openToPage(int pageNumber) override;
    void bookmarkPage(int pageNumber);

private:
    int totalPagesCount;
    int bookmarkedPageNumber;
};