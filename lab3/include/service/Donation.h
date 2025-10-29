#pragma once
#include <string>
#include <vector>
#include "Book.h"

class Donation {
public:
    Donation(const std::string& donor, double amount);
    void addBook(Book& book);
    void processDonation();

private:
    std::string donorName;
    double donationAmount;
    std::vector<Book> donatedBooks;
};