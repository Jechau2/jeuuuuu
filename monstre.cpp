#include <string>
#include <vector>

class Monstre {
public:
    // Basic attributes
    std::string nom;
    int niveau;
    int pointsDeVie;

    // Combat attributes
    int force;
    int defense;
    int agilite;

    // Rewards when the monster is defeated
    int experienceDonnee;
    int orDonne;
    std::vector<int> lootIds;

    Monstre(const std::string& nomInit,
            int niveauInit = 1,
            int pvInit = 50,
            int forceInit = 5,
            int defenseInit = 5,
            int agiliteInit = 5,
            int xpDonnee = 10,
            int orDonneInit = 1)
        : nom(nomInit),
          niveau(niveauInit),
          pointsDeVie(pvInit),
          force(forceInit),
          defense(defenseInit),
          agilite(agiliteInit),
          experienceDonnee(xpDonnee),
          orDonne(orDonneInit) {}

    bool estVivant() const { return pointsDeVie > 0; }
    void subirDegats(int degats) { pointsDeVie -= degats; if (pointsDeVie < 0) pointsDeVie = 0; }
};

