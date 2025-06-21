#include "inventory.h"

void Inventory::addItem(const std::string& item) {
    items.push_back(item);
}

void Inventory::removeItem(size_t index) {
    if (index < items.size()) {
        items.erase(items.begin() + static_cast<long>(index));
    }
}

const std::vector<std::string>& Inventory::getItems() const {
    return items;
}

