#include "LibraryCard.h"

LibraryCard::LibraryCard(int number, const std::string& issueDate)
    : cardNumber(number), issueDate(issueDate), expiryDate("через год") {}

void LibraryCard::renew() {
    expiryDate = "обновлено";
}

void LibraryCard::block() {
    expiryDate = "заблокировано";
}