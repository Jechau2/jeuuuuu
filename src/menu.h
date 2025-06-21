#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <string>

/**
 * @brief Affiche le menu principal du jeu.
 *
 * Cette fonction gère la boucle d'évènements et l'affichage du menu. Elle
 * permet de lancer une partie, charger une sauvegarde, accéder aux
 * paramètres ou quitter l'application.
 *
 * @param window     Fenêtre SDL pour l'affichage.
 * @param renderer   Rendu SDL associé à la fenêtre.
 * @param width      Largeur actuelle de la fenêtre (peut être modifiée).
 * @param height     Hauteur actuelle de la fenêtre (peut être modifiée).
 * @param targetFPS  Limite d'images par seconde souhaitée.
 * @param language   Langue utilisée dans l'interface.
 *
 * @return 0 si tout s'est bien passé, sinon un code d'erreur.
 */
int showMenu(SDL_Window* window, SDL_Renderer* renderer,
             int &width, int &height, int &targetFPS, std::string &language);

#endif // MENU_H
