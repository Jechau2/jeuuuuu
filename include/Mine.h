#ifndef MINE_H
#define MINE_H

#include <iostream>
#include <map>
#include <string>

#include "Random.h"

// Enumeration of ores for future extension
enum class TypeMinerai { Fer,
                         Or,
                         Argent };

inline std::string toString(TypeMinerai type) {
    switch (type) {
    case TypeMinerai::Fer:
        return "Fer";
    case TypeMinerai::Or:
        return "Or";
    default:
        return "Argent";
    }
}

struct Outil {
    std::string nom;
    int durabilite{0};
    int perteParExtraction{1};
};

class ZoneMinerai;

class Joueur {
    public:
    explicit Joueur(Outil outil) : outilActif(std::move(outil)) {}
    void extraire(ZoneMinerai& zone);
    void afficherStatut() const;

    std::map<std::string, int> ressources;
    Outil outilActif;
};

class ZoneMinerai {
    public:
    ZoneMinerai(std::string n, TypeMinerai t, int diff, int stockInit)
        : nom(std::move(n)), typeMinerai(t), difficulte(diff),
          stockInitial(stockInit), stock(stockInit) {}

    bool extraire(Joueur& joueur, int rng);

    std::string nom;
    TypeMinerai typeMinerai;
    int difficulte;   // 1-100
    int stockInitial; // initial quantity
    int stock;        // remaining quantity
};

#endif // MINE_H
