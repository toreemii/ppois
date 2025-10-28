#pragma once
#include <string>
#include "Freight.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include "Exceptions.h"

class Warehouse
{
private:
    std::string warehouseId;
    std::vector<Freight *> inventory;
    int capacity;
    std::string locationAddress;
    std::tm lastInspectionDate;
    bool hasSecuritySystem;
    double totalArea;
    int currentOccupancy;

public:
    Warehouse(std::string warehouseId, int capacity);
    void storeFreight(Freight *freight);
    void removeFreight(Freight *freight);
    bool checkCapacity();
    std::string getWarehouseId();
};