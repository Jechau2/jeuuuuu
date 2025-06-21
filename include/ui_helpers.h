#ifndef UI_HELPERS_H
#define UI_HELPERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

/**
 * @brief Teste si un point est à l'intérieur d'un rectangle.
 *
 * @param x Coordonnée X du point.
 * @param y Coordonnée Y du point.
 * @param r Rectangle de référence.
 * @return true si le point se trouve à l'intérieur du rectangle.
 */
bool pointInRect(int x, int y, const SDL_Rect& r);

/**
 * @brief Affiche une option de menu.
 *
 * Dessine un texte à la position donnée et met en surbrillance si
 * l'option est sélectionnée. Le rectangle de destination peut être retourné
 * pour détecter les clics.
 *
 * @param renderer Contexte de rendu SDL.
 * @param font     Police TTF utilisée pour le texte.
 * @param text     Chaîne à afficher.
 * @param x        Position horizontale.
 * @param y        Position verticale.
 * @param selected Met en valeur l'option si true.
 * @param outRect  Optionnel, renvoie la zone dessinée.
 */
void renderOption(SDL_Renderer* renderer, TTF_Font* font,
                  const std::string& text, int x, int y, bool selected,
                  SDL_Rect* outRect = nullptr);

/**
 * @brief Affiche une option de type "slider".
 *
 * Construit une ligne de texte contenant un label et plusieurs valeurs
 * sélectionnables, la valeur courante étant entourée de crochets.
 *
 * @param renderer Contexte de rendu SDL.
 * @param font     Police utilisée.
 * @param label    Nom de l'option.
 * @param options  Liste des valeurs possibles.
 * @param index    Index de la valeur courante dans options.
 * @param x        Position horizontale de rendu.
 * @param y        Position verticale de rendu.
 * @param selected Indique si l'option est sélectionnée.
 * @param outRect  Optionnel, renvoie la zone dessinée.
 */
void renderSliderOption(SDL_Renderer* renderer, TTF_Font* font,
                        const std::string& label,
                        const std::vector<std::string>& options,
                        int index, int x, int y, bool selected,
                        SDL_Rect* outRect = nullptr);

#endif // UI_HELPERS_H
