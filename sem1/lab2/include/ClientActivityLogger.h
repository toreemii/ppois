#pragma once
#include <iostream>
#include "./Client.h"

class Client;

class ClientActivityLogger
{
public:
    void logClientActivity(Client *client);
};
