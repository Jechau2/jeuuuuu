#include "jeu.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

/**
 * @brief Structure représentant le héros affiché dans l'interface.
 */
struct Character {
    std::string nom{"H\xC3\xA9ros"};
    int niveau{1};
    int pv{100};
    int pm{50};
    int force{10};
    int defense{10};
    int agilite{10};
    int intelligence{10};
};

/**
 * @brief Rend un texte à l'écran.
 *
 * Crée une texture à partir du texte fourni et l'affiche à la position donnée.
 *
 * @param renderer Contexte SDL de rendu.
 * @param font     Police utilisée pour le texte.
 * @param text     Chaîne à afficher.
 * @param x        Position horizontale.
 * @param y        Position verticale.
 */
static void renderText(SDL_Renderer* renderer, TTF_Font* font,
                       const std::string& text, int x, int y) {
    SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(),
                                               SDL_Color{255,255,255,255});
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dst{x, y, surf->w, surf->h};
    SDL_FreeSurface(surf);
    if (tex) {
        SDL_RenderCopy(renderer, tex, nullptr, &dst);
        SDL_DestroyTexture(tex);
    }
}

/**
 * @brief Boucle principale d'affichage du jeu.
 *
 * Affiche les statistiques du personnage et gère les entrées clavier pour
 * quitter la vue. Cette fonction bloque jusqu'à ce que l'utilisateur ferme la
 * fenêtre ou appuie sur Echap.
 *
 * @param window   Fenêtre SDL où afficher le jeu.
 * @param renderer Rendu associé à cette fenêtre.
 */
void showGame(SDL_Window* window, SDL_Renderer* renderer) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    int panelH = height / 3;
    SDL_Rect panel{0, height - panelH, width, panelH};

    Character hero;
    std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 200);
        SDL_RenderFillRect(renderer, &panel);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &panel);

        int x1 = panel.x + 10;
        int y = panel.y + 10;
        renderText(renderer, font, "Nom: " + hero.nom, x1, y); y += 24;
        renderText(renderer, font, "Niveau: " + std::to_string(hero.niveau), x1, y); y += 24;
        renderText(renderer, font, "PV: " + std::to_string(hero.pv), x1, y); y += 24;
        renderText(renderer, font, "PM: " + std::to_string(hero.pm), x1, y);

        int x2 = panel.x + width / 2;
        y = panel.y + 10;
        renderText(renderer, font, "Force: " + std::to_string(hero.force), x2, y); y += 24;
        renderText(renderer, font, "Defense: " + std::to_string(hero.defense), x2, y); y += 24;
        renderText(renderer, font, "Agilite: " + std::to_string(hero.agilite), x2, y); y += 24;
        renderText(renderer, font, "Intelligence: " + std::to_string(hero.intelligence), x2, y);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
}

