#include "../include/Security.h"

Security::Security(std::string securityId) : securityId(securityId) {}

std::string Security::getSecurityId()
{
    return securityId;
}
bool Security::checkVehicleSafety(Vehicle *vehicle)
{
    bool isSafe = vehicle->getStatus() != "На загрузке";
    if (isSafe)
    {
        std::cout << "Транспорт проверен на безопасность: " << securityId << std::endl;
    }
    else
    {
        std::cout << "Транспорт не прошёл проверку безопасности: " << securityId << std::endl;
    }
    return isSafe;
}

bool Security::checkFreightSafety(Freight *freight)
{
    if (freight->isHazardous())
    {
        return false;
    }
    return true;
}

void Security::logSecurityIncident() const
{
    std::cout << "Инцидент зарегистрирован " << securityId << " в " << std::asctime(&lastCheckDate) << std::endl;
}

void Security::updateSecurityLevel(int level)
{
    if (level >= 0 && level <= 5)
    {
        securityLevel = level;
    }
}