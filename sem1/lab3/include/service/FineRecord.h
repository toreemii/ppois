#pragma once
class FineRecord {
public:
    FineRecord(int memberId, double amount);
    void markAsPaid();
    bool isPaid() const;

private:
    int memberIdentification;
    double fineAmount;
    bool isPaidStatus;
};