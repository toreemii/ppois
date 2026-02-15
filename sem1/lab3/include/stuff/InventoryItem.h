#pragma once
#include <string>

class InventoryItem {
public:
    InventoryItem(int itemId, const std::string& name, int quantity);
    void addStock(int amount);
    void removeStock(int amount);

private:
    int itemIdentification;
    std::string itemName;
    int currentQuantity;
};