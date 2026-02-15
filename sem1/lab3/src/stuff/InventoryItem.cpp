#include "InventoryItem.h"

InventoryItem::InventoryItem(int itemId, const std::string& name, int quantity)
    : itemIdentification(itemId), itemName(name), currentQuantity(quantity) {}

void InventoryItem::addStock(int amount) {
    if (amount > 0) {
        currentQuantity += amount;
    }
}

void InventoryItem::removeStock(int amount) {
    if (amount > 0 && currentQuantity >= amount) {
        currentQuantity -= amount;
    }
}