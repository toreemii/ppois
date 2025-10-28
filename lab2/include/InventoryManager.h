#pragma once
#include <string>
#include <vector>
#include "Warehouse.h"
class InventoryManager
{
private:
    std::string managerId;
    std::vector<Warehouse *> warehouses;

public:
    InventoryManager(std::string managerId, std::vector<Warehouse *> warehouses);
    InventoryManager(std::string managerId) : managerId(managerId) {}
    void addWarehouse(Warehouse *warehouse);
    void manageInventory(Freight *freight, Warehouse *warehouse);
    std::string getManagerId();
};