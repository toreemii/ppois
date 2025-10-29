#pragma once
#include "Book.h"
#include <string>

class BookCopy {
public:
    BookCopy(const Book& originalBook, int copyId);
    void markAsAvailable();
    void markAsBorrowed();

private:
    Book originalBookReference;
    int copyIdentification;
    bool isAvailable;
};