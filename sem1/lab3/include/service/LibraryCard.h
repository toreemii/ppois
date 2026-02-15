#pragma once
#include <string>

class LibraryCard {
public:
    LibraryCard(int number, const std::string& issueDate);
    void renew();
    void block();

private:
    int cardNumber;
    std::string issueDate;
    std::string expiryDate;
};