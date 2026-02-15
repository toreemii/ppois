#include "../include/ClientActivityLogger.h"

void ClientActivityLogger::logClientActivity(Client *client)
{
    std::cout << "Лог: активность клиента " << client->getName() << " зафиксирована." << std::endl;
}

