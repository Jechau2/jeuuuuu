#ifndef CHARACTER_H
#define CHARACTER_H

#include "inventory.h"
#include <string>
#include <limits>

struct Character {
    std::string nom{"H\xC3\xA9ros"};
    int niveau{1};
    int pv{100};
    int pm{50};
    int force{10};
    int defense{10};
    int agilite{10};
    int intelligence{10};
    int sprite{0};
    Inventory inventaire;
};

#endif // CHARACTER_H
