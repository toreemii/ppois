#pragma once
#include <string>
#include "Vehicle.h"

class SafetyProtocol
{
private:
    std::string protocolId;

public:
    SafetyProtocol(std::string protocolId);
    std::string getProtocolId();
    void applyProtocol(Vehicle *vehicle);
};