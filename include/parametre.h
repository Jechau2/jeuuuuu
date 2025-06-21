#ifndef PARAMETRE_H
#define PARAMETRE_H

#include <SDL2/SDL.h>
#include <string>

/**
 * @brief Affiche le menu des paramètres.
 *
 * Permet à l'utilisateur de modifier la langue, la taille de la fenêtre et la
 * cadence d'affichage (FPS). Les valeurs choisies sont renvoyées via les
 * références passées en paramètre.
 *
 * @param window   Fenêtre SDL cible.
 * @param renderer Rendu utilisé pour l'affichage.
 * @param width    Largeur de fenêtre à mettre à jour.
 * @param height   Hauteur de fenêtre à mettre à jour.
 * @param fps      Nombre d'images par seconde choisi.
 * @param language Langue de l'interface sélectionnée.
 */
void showSettings(SDL_Window* window, SDL_Renderer* renderer,
                  int &width, int &height, int &fps, std::string &language);

#endif // PARAMETRE_H
