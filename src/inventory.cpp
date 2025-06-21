#include "inventory.h"

void Inventory::addItem(const std::string& item) {
    items.push_back(item);
}

const std::vector<std::string>& Inventory::getItems() const {
    return items;
}

