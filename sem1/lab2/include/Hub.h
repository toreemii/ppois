#pragma once
#include <vector>
#include <string>
#include "Route.h"
#include "Shipment.h"
class Hub
{
private:
    std::string hubId;
    std::vector<Shipment*> incoming;
    std::vector<Shipment*> outgoing;
    int capacity;

public:
    Hub(std::string hubId, int capacity);
    void transShip(Shipment *shipment);
    void sortByDestination(Route *route);
    bool checkCapacity();
    std::string getHubId();
};