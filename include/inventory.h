#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>

class Inventory {
public:
    void addItem(const std::string& item);
    void removeItem(size_t index);
    const std::vector<std::string>& getItems() const;
private:
    std::vector<std::string> items;
};

#endif // INVENTORY_H
