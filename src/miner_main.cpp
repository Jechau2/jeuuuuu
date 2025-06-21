#include "Mine.h"
#include <iostream>
#include <vector>

int main() {
    Outil pioche{"Pioche rudimentaire", 5, 1};
    Joueur joueur(pioche);
    std::vector<ZoneMinerai> zones{
        {"Carriere", TypeMinerai::Fer, 20, 5},
        {"Mine ancienne", TypeMinerai::Or, 50, 3},
        {"Grotte mysterieuse", TypeMinerai::Argent, 80, 2}};
    ZoneMinerai* zoneCourante = &zones[0];

    int choix = 0;
    while (choix != 4) {
        std::cout << "\n=== Menu Mine ===\n";
        std::cout << "Zone actuelle: " << zoneCourante->nom << "\n";
        std::cout << "[1] Choisir zone\n";
        std::cout << "[2] Examiner inventaire / outil\n";
        std::cout << "[3] Extraire dans zone courante\n";
        std::cout << "[4] Quitter\n";
        std::cout << "Choix: ";
        std::cin >> choix;
        switch (choix) {
        case 1: {
            for (size_t i = 0; i < zones.size(); ++i) {
                std::cout << i + 1 << ". " << zones[i].nom
                          << " (stock: " << zones[i].stock << ")\n";
            }
            size_t zi = 0;
            std::cin >> zi;
            if (zi >= 1 && zi <= zones.size())
                zoneCourante = &zones[zi - 1];
            break;
        }
        case 2:
            joueur.afficherStatut();
            break;
        case 3:
            joueur.extraire(*zoneCourante);
            break;
        case 4:
            std::cout << "Au revoir !\n";
            break;
        default:
            std::cout << "Choix invalide." << std::endl;
        }
    }
    return 0;
}
