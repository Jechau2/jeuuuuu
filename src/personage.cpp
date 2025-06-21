#include <string>
#include <vector>

class Personage {
public:
    // Basic attributes
    std::string nom;
    int niveau;
    int pointsDeVie;
    int pointsDeMagie;

    // Combat attributes
    int force;
    int defense;
    int agilite;
    int intelligence;

    // Inventory and equipment
    std::vector<int> inventaire;
    int armeEquipped;
    int armureEquipped;

    Personage(const std::string& nomInit,
              int niveauInit = 1,
              int pv = 100,
              int pm = 50)
        : nom(nomInit),
          niveau(niveauInit),
          pointsDeVie(pv),
          pointsDeMagie(pm),
          force(10),
          defense(10),
          agilite(10),
          intelligence(10),
          armeEquipped(-1),
          armureEquipped(-1) {}
};
