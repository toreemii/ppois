#pragma once
#include "Client.h"
#include <iostream>
#include "Exceptions.h"

class Client;

class LoyaltyManager
{
public:
    void applyLoyaltyDiscount(Client *client, double percentage);
    bool checkEligibilityForPriority(const Client *client);
    void logClientActivity(Client *client);
};