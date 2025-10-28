#include "../include/Schedule.h"

Schedule::Schedule(std::string scheduleId, std::string timeSlot, Vehicle *vehicle, Driver *driver, Order *order)
    : scheduleId(scheduleId), timeSlot(timeSlot), vehicle(vehicle), driver(driver), order(order) {}

void Schedule::assignSchedule()
{
    if (vehicle && driver)
    {
        vehicle->assignDriver(*driver);
        if (order)
        {
            order->assignVehicleAndEmployee(vehicle, driver);
            std::cout << "Расписание " << scheduleId << " назначено для заказа " << order->getOrderId()
                      << " на время " << timeSlot << std::endl;
        }
        else
        {
            std::cout << "Расписание " << scheduleId << " назначено на время " << timeSlot << std::endl;
        }
    }
    else
    {
        throw std::runtime_error("Транспорт или водитель не назначены");
    }
}
void Schedule::cancelSchedule()
{
    if (vehicle)
        vehicle->setStatus(1); 
    std::cout << "Расписание " << scheduleId << " отменено" << std::endl;
}
std::string Schedule::getScheduleId()
{
    return scheduleId;
}
std::string Schedule::getTimeSlot()
{
    return timeSlot;
}
void Schedule::setOrder(Order *order)
{
    this->order = order;
    std::cout << "Заказ " << order->getOrderId() << " добавлен в расписание " << scheduleId << std::endl;
}