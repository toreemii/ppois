#pragma once
#include <string>

class AccessCard {
public:
    AccessCard(int cardId, const std::string& owner);
    void activate();
    void deactivate();

private:
    int cardIdentification;
    std::string ownerName;
    bool isActive;
};