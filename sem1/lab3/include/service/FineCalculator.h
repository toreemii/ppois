#pragma once
class FineCalculator {
public:
    double calculateFine(int daysOverdue);
    void resetFine();
    double getCurrentFine() const;

private:
    double currentFineAmount;
};