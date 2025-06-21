#include <string>

/**
 * @brief Représente un objet dans le jeu.
 */
class Objet {
public:
    int id;
    std::string nom;
    std::string description;

    /**
     * @brief Constructeur d'Objet.
     * @param identifiant Identifiant unique de l'objet.
     * @param nom Nom de l'objet.
     * @param description Description textuelle.
     */
    Objet(int identifiant, const std::string& nom, const std::string& description)
        : id(identifiant), nom(nom), description(description) {}
};
