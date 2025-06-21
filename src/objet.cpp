#include <string>

class Objet {
public:
    int id;
    std::string nom;
    std::string description;

    Objet(int identifiant, const std::string& nom, const std::string& description)
        : id(identifiant), nom(nom), description(description) {}
};
