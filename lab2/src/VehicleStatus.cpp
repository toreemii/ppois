#include "../include/VehicleStatus.h"

VehicleStatus::VehicleStatus(int initialStatus, int priority, bool operational)
    : statusPriority(priority), isOperational(operational)
{
    statusMap = {
        {0, "Non-operational"},
        {1, "Operational"},
        {2, "In route"}};
    setStatus(initialStatus);
}

std::string VehicleStatus::getStatus()
{
    return status;
}

std::time_t VehicleStatus::getLastStatusChange()
{
    return lastStatusChange;
}

void VehicleStatus::setStatus(int statusState)
{
    auto it = statusMap.find(statusState);
    if (it == statusMap.end())
    {
        throw InvalidStatusException();
    }
    status = it->second;
    lastStatusChange = std::time(nullptr);
}

bool VehicleStatus::isValidStatus(int statusState)
{
    return statusMap.find(statusState) != statusMap.end();
}
