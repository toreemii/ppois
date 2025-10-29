#include "AccessCard.h"

AccessCard::AccessCard(int cardId, const std::string& owner)
    : cardIdentification(cardId), ownerName(owner), isActive(true) {}

void AccessCard::activate() {
    isActive = true;
}

void AccessCard::deactivate() {
    isActive = false;
}