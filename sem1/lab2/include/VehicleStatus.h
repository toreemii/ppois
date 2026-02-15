#pragma once
#include <string>
#include <map>
#include <ctime>
#include "Exceptions.h"

class VehicleStatus
{
private:
    std::string status;
    std::map<int, std::string> statusMap = {{-1, "На загрузке"}, {0, "В пути"}, {1, "Прибыл"}};
    std::string statusDescription;
    std::string statusCode;
    std::time_t lastStatusChange;
    int statusPriority;
    bool isOperational;

public:
    VehicleStatus(int initialStatus = 0, int priority = 0, bool operational = true);
    std::string getStatus();
    void setStatus(int statusState);
    std::time_t getLastStatusChange();
    bool isValidStatus(int statusState);
};