#ifndef JEU_H
#define JEU_H

#include <SDL2/SDL.h>

/**
 * @brief Affiche l'interface principale du jeu.
 *
 * Cette fonction lance la boucle de rendu du jeu et affiche les
 * statistiques du héros ainsi que les différents panneaux graphiques.
 *
 * @param window   Fenêtre SDL dans laquelle afficher le jeu.
 * @param renderer Rendu SDL utilisé pour dessiner.
 */
void showGame(SDL_Window* window, SDL_Renderer* renderer);

#endif // JEU_H
