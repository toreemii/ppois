#pragma once
#include <string>
#include "Vehicle.h"
#include "Order.h"
#include "Driver.h"

class Schedule
{
private:
    std::string scheduleId;
    std::string timeSlot;
    Vehicle *vehicle;
    Driver *driver;
    Order *order;
    
public:
    Schedule(std::string scheduleId, std::string timeSlot, Vehicle* vehicle, Driver* driver, Order* order = nullptr);
    void assignSchedule();
    void cancelSchedule();
    std::string getScheduleId();
    std::string getTimeSlot();
    void setOrder(Order* order);
};