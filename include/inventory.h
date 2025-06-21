#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

/**
 * @brief Gestion basique d'un inventaire textuel.
 */
class Inventory {
    public:
    /** Ajoute un objet à l'inventaire. */
    void addItem(const std::string& item);

    /** Supprime un objet à l'index donné. */
    void removeItem(size_t index);

    /** Retourne la liste des objets. */
    const std::vector<std::string>& getItems() const;

    private:
    std::vector<std::string> items;
};

#endif // INVENTORY_H
