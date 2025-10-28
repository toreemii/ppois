#include "../include/MaintenanceScheduler.h"

MaintenanceScheduler::MaintenanceScheduler(std::string schedulerId) : schedulerId(schedulerId) {}

std::string MaintenanceScheduler::getSchedulerId()
{
    return schedulerId;
}
void MaintenanceScheduler::scheduleMaintenance(Vehicle *vehicle, Maintenance *maintenance)
{
    maintenance->fixPart("Двигатель");
    vehicle->setStatus(-1);
    std::cout << "Техобслуживание запланировано: " << schedulerId << std::endl;
}