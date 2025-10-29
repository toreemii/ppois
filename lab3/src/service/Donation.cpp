#include "Donation.h"

Donation::Donation(const std::string& donor, double amount)
    : donorName(donor), donationAmount(amount) {}

void Donation::addBook(Book& book) {
    donatedBooks.push_back(book);
}

void Donation::processDonation() {
    if (donationAmount > 0 || !donatedBooks.empty()) {
    }
}