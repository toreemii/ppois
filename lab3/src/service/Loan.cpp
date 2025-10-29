#include "Loan.h"
#include "LibraryExceptions.h"

Loan::Loan(Book& loanedBook, Member& borrowerMember, const std::string& dueDate)
    : associatedBook(loanedBook), associatedMember(borrowerMember), loanDueDate(dueDate) {}

void Loan::extendDueDate(const std::string& newDueDate) {
    if (!newDueDate.empty()) {
        loanDueDate = newDueDate;
    }
}

void Loan::validateLoan() {
    if (loanDueDate.empty()) {
        LibraryExceptions::throwInvalidLoan("Пустая дата возврата");
    }
}

Book& Loan::getAssociatedBook() {
    return associatedBook;
}