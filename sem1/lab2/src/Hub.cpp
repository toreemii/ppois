#include "../include/Hub.h"

Hub::Hub(std::string hubId, int capacity) : hubId(hubId), capacity(capacity) {}

std::string Hub::getHubId()
{
    return hubId;
}
void Hub::transShip(Shipment *shipment)
{
    if (incoming.size() < capacity)
    {
        incoming.push_back(shipment);
        std::cout << "Груз " << shipment->getShipmentId() << " перегружен в хабе " << hubId << std::endl;
    }
    else
    {
        throw std::runtime_error("Пропускная способность превышена");
    }
}
void Hub::sortByDestination(Route *route)
{
    std::cout << "Отправления отсортированы по месту назначения для маршрута" << route->getRouteId() << std::endl;
}
bool Hub::checkCapacity()
{
    return incoming.size() < capacity;
}
