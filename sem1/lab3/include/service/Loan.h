#pragma once
#include "Book.h"
#include "Member.h"
#include <string>

class Loan
{
public:
    Loan(const Loan &other)
        : associatedBook(other.associatedBook),
          associatedMember(other.associatedMember),
          loanDueDate(other.loanDueDate) {}
    Loan(Book &loanedBook, Member &borrowerMember, const std::string &dueDate);
    void extendDueDate(const std::string &newDueDate);
    void validateLoan();
    Book &getAssociatedBook();

private:
    Book &associatedBook;
    Member &associatedMember;
    std::string loanDueDate;
};