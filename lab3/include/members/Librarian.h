#pragma once
#include "Staff.h"
#include "Book.h"
#include "Member.h"

class Librarian : public Staff {
public:
    Librarian(const std::string& name, int employeeId);
    void issueBookToMember(Book& bookToIssue, Member& memberToIssueTo);
    void collectFineFromMember(Member& memberToCollectFrom, double amount);

private:
    int issuedBooksCount;
};