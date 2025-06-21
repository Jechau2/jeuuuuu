#ifndef MINE_H
#define MINE_H

#include <iostream>
#include <map>
#include <string>

#include "Random.h"

/**
 * @brief Types de minerai disponibles.
 */
enum class TypeMinerai {
    Fer,
    Or,
    Argent
};

/**
 * @brief Convertit un type de minerai en chaîne.
 */
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

/**
 * @brief Décrit un outil utilisé pour l'extraction.
 */
struct Outil {
    std::string nom;
    int durabilite{0};
    int perteParExtraction{1};
};

class ZoneMinerai;

class Joueur {
    public:
    explicit Joueur(Outil outil) : outilActif(std::move(outil)) {}

    /**
     * @brief Tente d'extraire du minerai depuis une zone.
     */
    void extraire(ZoneMinerai& zone);

    /**
     * @brief Affiche le contenu de l'inventaire du joueur.
     */
    void afficherStatut() const;

    std::map<std::string, int> ressources;
    Outil outilActif;
};

class ZoneMinerai {
    public:
    ZoneMinerai(std::string n, TypeMinerai t, int diff, int stockInit)
        : nom(std::move(n)), typeMinerai(t), difficulte(diff),
          stockInitial(stockInit), stock(stockInit) {}

    /**
     * @brief Effectue une tentative d'extraction.
     */
    bool extraire(Joueur& joueur, int rng);

    std::string nom;
    TypeMinerai typeMinerai;
    int difficulte;   // 1-100
    int stockInitial; // initial quantity
    int stock;        // remaining quantity
};

#endif // MINE_H
