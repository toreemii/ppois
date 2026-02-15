#include "Borrower.h"

Borrower::Borrower(const std::string& name, int memberId) : Member(name, memberId) {}

void Borrower::borrowBook(Book& bookToBorrow) {
    borrowedBooksList.push_back(bookToBorrow);
}

void Borrower::returnBook(const std::string& bookTitle) {
    for (size_t index = 0; index < borrowedBooksList.size(); ++index) {
        if (borrowedBooksList[index].getPublicationTitle() == bookTitle) {
            borrowedBooksList.erase(borrowedBooksList.begin() + index);
            return;
        }
    }
}