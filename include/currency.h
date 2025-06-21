#ifndef CURRENCY_H
#define CURRENCY_H

#include <cstdint>

/**
 * @brief Gestion d'une monnaie avec conversions automatiques.
 */
class Currency {
    public:
    /** Ajoute des pièces de bronze. */
    void addBronze(int64_t amount);
    /** Ajoute des pièces d'argent. */
    void addSilver(int64_t amount);
    /** Ajoute des pièces d'or. */
    void addGold(int64_t amount);
    /** Ajoute des pièces de platine. */
    void addPlatinum(int64_t amount);

    /** Retire des pièces de bronze, retourne false si insuffisant. */
    bool subtractBronze(int64_t amount);

    /** Nombre total de pièces exprimé en bronze. */
    int64_t totalBronze() const;

    /** Nombre de pièces de bronze après conversion. */
    int bronze() const;
    /** Nombre de pièces d'argent après conversion. */
    int silver() const;
    /** Nombre de pièces d'or après conversion. */
    int gold() const;
    /** Nombre de pièces de platine après conversion. */
    int platinum() const;

    private:
    int64_t total_{0};
};

#endif // CURRENCY_H
