#include "Librarian.h"

Librarian::Librarian(const std::string& name, int employeeId) : Staff(name, employeeId), issuedBooksCount(0) {}

void Librarian::issueBookToMember(Book& bookToIssue, Member& memberToIssueTo) {
    issuedBooksCount++;
    memberToIssueTo.updateMembershipStatus();
}

void Librarian::collectFineFromMember(Member& memberToCollectFrom, double amount) {
    if (amount > 0) {
        memberToCollectFrom.updateMembershipStatus();
    }
}