#include "LoanManager.h"
#include "LibraryExceptions.h"

void LoanManager::addLoanToRecords(Loan& loanToAdd) {
    managedLoans.push_back(loanToAdd);
}

void LoanManager::removeLoanFromRecords(const std::string& bookTitle) {
    for (size_t index = 0; index < managedLoans.size(); ++index) {
        if (managedLoans[index].getAssociatedBook().getPublicationTitle() == bookTitle) {
            managedLoans.erase(managedLoans.begin() + index);
            return;
        }
    }
}

Loan* LoanManager::findLoanByBook(const std::string& bookTitle) {
    for (size_t index = 0; index < managedLoans.size(); ++index) {
        if (managedLoans[index].getAssociatedBook().getPublicationTitle() == bookTitle) {
            return &managedLoans[index];
        }
    }
    LibraryExceptions::throwInvalidLoan("Заём не найден");  
    return nullptr;
}