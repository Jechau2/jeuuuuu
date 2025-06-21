#include "inventory.h"

/**
 * @brief Ajoute un objet dans l'inventaire.
 */
void Inventory::addItem(const std::string& item) {
    items.push_back(item);
}

/**
 * @brief Supprime l'objet à l'index indiqué s'il existe.
 */
void Inventory::removeItem(size_t index) {
    if (index < items.size()) {
        items.erase(items.begin() + static_cast<long>(index));
    }
}

/**
 * @brief Renvoie la liste des objets présents.
 */
const std::vector<std::string>& Inventory::getItems() const {
    return items;
}
