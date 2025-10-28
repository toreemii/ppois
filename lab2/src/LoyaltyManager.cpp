#include "../include/LoyaltyManager.h"

void LoyaltyManager::applyLoyaltyDiscount(Client *client, double percentage)
{
    if (percentage > 0 && percentage <= 100)
    {
        client->setDiscountRate(percentage / 100);
    }
}

bool LoyaltyManager::checkEligibilityForPriority(const Client *client)
{
    return client->getLoyaltyPoints() >= 100;
}

void LoyaltyManager::logClientActivity(Client *client)
{
    std::cout << "Лог: активность клиента " << client->getName() << " зафиксирована." << std::endl;
}