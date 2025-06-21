#include <string>
#include <vector>

/**
 * @brief Décrit un monstre rencontré dans le jeu.
 */
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

    /**
     * @brief Constructeur d'un monstre.
     *
     * @param nomInit       Nom du monstre.
     * @param niveauInit    Niveau initial.
     * @param pvInit        Points de vie de départ.
     * @param forceInit     Valeur de force initiale.
     * @param defenseInit   Valeur de défense initiale.
     * @param agiliteInit   Valeur d'agilité initiale.
     * @param xpDonnee      Expérience donnée à la mort.
     * @param orDonneInit   Quantité d'or donnée.
     */
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

    /**
     * @brief Vérifie si le monstre est encore en vie.
     * @return true si ses points de vie sont supérieurs à 0.
     */
    bool estVivant() const { return pointsDeVie > 0; }

    /**
     * @brief Applique des dégâts au monstre.
     * @param degats Nombre de points à retirer.
     */
    void subirDegats(int degats) { pointsDeVie -= degats; if (pointsDeVie < 0) pointsDeVie = 0; }
};

