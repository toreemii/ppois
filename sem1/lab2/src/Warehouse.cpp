#include "../include/Warehouse.h"

Warehouse::Warehouse(std::string warehouseId, int capacity) : warehouseId(warehouseId), capacity(capacity) {}

std::string Warehouse::getWarehouseId()
{
    return warehouseId;
}
void Warehouse::storeFreight(Freight *freight)
{
    if (inventory.size() < capacity)
    {
        inventory.push_back(freight);
        std::cout << "Груз " << freight->getFreightId() << " помещён на склад " << warehouseId << std::endl;
    }
    else
    {
        throw CapacityExceededException();
    }
}
void Warehouse::removeFreight(Freight *freight)
{
    auto it = std::find(inventory.begin(), inventory.end(), freight);
    if (it != inventory.end())
    {
        inventory.erase(it);
        std::cout << "Груз " << freight->getFreightId() << " удалён со склада " << warehouseId << std::endl;
    }
}
bool Warehouse::checkCapacity()
{
    return inventory.size() < capacity;
}
