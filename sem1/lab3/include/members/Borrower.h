#pragma once
#include "Member.h"
#include <vector>
#include "Book.h"

class Borrower : public Member {
public:
    Borrower(const std::string& name, int memberId);
    void borrowBook(Book& bookToBorrow);
    void returnBook(const std::string& bookTitle);

private:
    std::vector<Book> borrowedBooksList;
};