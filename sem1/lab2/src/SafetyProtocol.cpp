#include "../include/SafetyProtocol.h"

SafetyProtocol::SafetyProtocol(std::string protocolId) : protocolId(protocolId) {}

std::string SafetyProtocol::getProtocolId()
{
    return protocolId;
}
void SafetyProtocol::applyProtocol(Vehicle *vehicle)
{
    std::cout << "Протокол безопасности применён к транспорту: " << protocolId << std::endl;
}