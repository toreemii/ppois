#pragma once
#include <vector>
#include "Loan.h"

class LoanManager {
public:
    void addLoanToRecords(Loan& loanToAdd);
    void removeLoanFromRecords(const std::string& bookTitle);
    Loan* findLoanByBook(const std::string& bookTitle);

private:
    std::vector<Loan> managedLoans;
};