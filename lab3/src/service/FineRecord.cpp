#include "FineRecord.h"

FineRecord::FineRecord(int memberId, double amount)
    : memberIdentification(memberId), fineAmount(amount), isPaidStatus(false) {}

void FineRecord::markAsPaid() {
    isPaidStatus = true;
}

bool FineRecord::isPaid() const {
    return isPaidStatus;
}