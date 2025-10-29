#include "FineCalculator.h"

double FineCalculator::calculateFine(int daysOverdue) {
    if (daysOverdue > 0) {
        currentFineAmount = daysOverdue * 10.0;
    }
    return currentFineAmount;
}

void FineCalculator::resetFine() {
    currentFineAmount = 0.0;
}

double FineCalculator::getCurrentFine() const {
    return currentFineAmount;
}