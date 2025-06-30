#include "save_system.h"
#include <cstdint>
#include <fstream>

bool saveCharacter(const Character& hero, const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs)
        return false;
    ofs << hero.nom << '\n'
        << hero.niveau << ' ' << hero.pv << ' ' << hero.pm << ' '
        << hero.force << ' ' << hero.defense << ' ' << hero.agilite << ' '
        << hero.intelligence << ' ' << hero.monnaie.totalBronze() << '\n';
    const auto& items = hero.inventaire.getItems();
    ofs << items.size() << '\n';
    for (const auto& it : items)
        ofs << it << '\n';
    return true;
}

bool loadCharacter(Character& hero, const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs)
        return false;
    std::getline(ifs, hero.nom);
    int64_t money;
    ifs >> hero.niveau >> hero.pv >> hero.pm >> hero.force >> hero.defense >> hero.agilite >> hero.intelligence >> money;
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    hero.monnaie = Currency();
    hero.monnaie.addBronze(money);
    size_t itemCount = 0;
    ifs >> itemCount;
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    hero.inventaire = Inventory();
    for (size_t i = 0; i < itemCount; ++i) {
        std::string item;
        std::getline(ifs, item);
        hero.inventaire.addItem(item);
    }
    return true;
}
