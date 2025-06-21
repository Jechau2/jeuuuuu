#include "Mine.h"
#include <chrono>
#include <thread>

static void showProgress() {
    const int barWidth = 20;
    for (int i = 0; i < barWidth; ++i) {
        std::cout << '\r' << '[' << std::string(i + 1, '#')
                  << std::string(barWidth - i - 1, ' ') << ']';
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << std::endl;
}

void Joueur::extraire(ZoneMinerai& zone) {
    if (outilActif.durabilite <= 0) {
        std::cout << "Votre outil est cass\xC3\xA9 !\n";
        return;
    }
    showProgress();
    int rng = Random::range(1, 100);
    bool reussite = zone.extraire(*this, rng);
    if (reussite) {
        outilActif.durabilite -= outilActif.perteParExtraction;
        if (outilActif.durabilite <= 0) {
            outilActif.durabilite = 0;
            std::cout << "Votre outil s'est cass\xC3\xA9 !\n";
        }
    }
}

void Joueur::afficherStatut() const {
    std::cout << "Outil: " << outilActif.nom
              << " (durabilit\xC3\xA9: " << outilActif.durabilite << ")\n";
    std::cout << "Inventaire:" << std::endl;
    if (ressources.empty()) {
        std::cout << "  (vide)\n";
    }
    for (const auto& p : ressources) {
        std::cout << "  " << p.first << " x" << p.second << std::endl;
    }
}

bool ZoneMinerai::extraire(Joueur& joueur, int rng) {
    if (stock <= 0) {
        std::cout << "La zone est \xC3\xA9puis\xC3\xA9e.\n";
        return false;
    }
    int chance = 100 - difficulte;
    if (rng <= chance) {
        --stock;
        joueur.ressources[toString(typeMinerai)]++;
        std::cout << "Extraction r\xC3\xA9ussie !" << std::endl;
        return true;
    }
    std::cout << "Extraction \xC3\xA9chou\xC3\xA9e." << std::endl;
    return false;
}

// TODO: ajouter craft d'outils
// TODO: sauvegarde fichier
// TODO: tests unitaires
