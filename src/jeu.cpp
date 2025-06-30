#include "jeu.h"
#include "GameAI.h"
#include "character.h"
#include "currency.h"
#include "inventory.h"
#include "save_system.h"
#include "ui_helpers.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

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
                                               SDL_Color{255, 255, 255, 255});
    if (!surf)
        return;
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
void showGame(SDL_Window* window, SDL_Renderer* renderer, Character& hero) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    int panelH = height / 3;
    SDL_Rect panel{0, height - panelH, width, panelH};
    SDL_Rect invButton{panel.x + width - 150, panel.y + 10, 140, 30};

    if (hero.monnaie.totalBronze() == 0)
        hero.monnaie.addGold(1); // monnaie initiale
    if (hero.inventaire.getItems().empty()) {
        hero.inventaire.addItem("Potion de soin");
        hero.inventaire.addItem("Epee en bois");
        hero.inventaire.addItem("Bouclier");
    }
    std::vector<std::string> labItems;
    GameAI ai;
    std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    bool running = true;
    bool inventoryOpen = false;
    SDL_Event e;
    SDL_Rect invRect{50, 50, width - 100, height - 100};
    SDL_Rect labRect{invRect.x + 20, invRect.y + 20, invRect.w - 40, 80};
    SDL_Rect searchBtn{labRect.x + labRect.w - 110, labRect.y + labRect.h + 10, 100, 30};
    std::vector<SDL_Rect> itemRects;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (inventoryOpen) {
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                    inventoryOpen = false;
                else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    int mx = e.button.x;
                    int my = e.button.y;
                    if (pointInRect(mx, my, searchBtn)) {
                        if (!labItems.empty()) {
                            std::string prompt = "Combine les objets suivants pour en creer un nouveau : ";
                            for (size_t i = 0; i < labItems.size(); ++i) {
                                prompt += labItems[i];
                                if (i + 1 < labItems.size())
                                    prompt += ", ";
                            }
                            std::string result = ai.generateObject(prompt);
                            if (!result.empty())
                                hero.inventaire.addItem(result);
                            labItems.clear();
                        }
                    } else {
                        for (size_t i = 0; i < itemRects.size(); ++i) {
                            if (pointInRect(mx, my, itemRects[i])) {
                                if (labItems.size() < 3) {
                                    labItems.push_back(hero.inventaire.getItems()[i]);
                                    hero.inventaire.removeItem(i);
                                }
                                break;
                            }
                        }
                    }
                }
            } else {
                if (e.type == SDL_QUIT)
                    running = false;
                else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                        running = false;
                    else if (e.key.keysym.sym == SDLK_s)
                        saveCharacter(hero, "savegame.txt");
                    else if (e.key.keysym.sym == SDLK_l)
                        loadCharacter(hero, "savegame.txt");
                } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    int mx = e.button.x;
                    int my = e.button.y;
                    if (pointInRect(mx, my, invButton))
                        inventoryOpen = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 200);
        SDL_RenderFillRect(renderer, &panel);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &panel);

        int x1 = panel.x + 10;
        int y = panel.y + 10;
        renderText(renderer, font, "Nom: " + hero.nom, x1, y);
        y += 24;
        renderText(renderer, font, "Niveau: " + std::to_string(hero.niveau), x1, y);
        y += 24;
        renderText(renderer, font, "PV: " + std::to_string(hero.pv), x1, y);
        y += 24;
        renderText(renderer, font, "PM: " + std::to_string(hero.pm), x1, y);
        y += 24;
        std::string money = "Monnaie: " + std::to_string(hero.monnaie.platinum()) + "P " +
                            std::to_string(hero.monnaie.gold()) + "G " +
                            std::to_string(hero.monnaie.silver()) + "A " +
                            std::to_string(hero.monnaie.bronze()) + "B";
        renderText(renderer, font, money, x1, y);

        int x2 = panel.x + width / 2;
        y = panel.y + 10;
        renderText(renderer, font, "Force: " + std::to_string(hero.force), x2, y);
        y += 24;
        renderText(renderer, font, "Defense: " + std::to_string(hero.defense), x2, y);
        y += 24;
        renderText(renderer, font, "Agilite: " + std::to_string(hero.agilite), x2, y);
        y += 24;
        renderText(renderer, font, "Intelligence: " + std::to_string(hero.intelligence), x2, y);

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &invButton);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &invButton);
        int tw, th;
        TTF_SizeUTF8(font, "Inventaire", &tw, &th);
        renderText(renderer, font, "Inventaire",
                   invButton.x + (invButton.w - tw) / 2,
                   invButton.y + (invButton.h - th) / 2);

        if (inventoryOpen) {
            itemRects.clear();
            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 230);
            SDL_RenderFillRect(renderer, &invRect);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &invRect);

            // Lab area
            SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
            SDL_RenderFillRect(renderer, &labRect);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &labRect);
            renderText(renderer, font, "Lab", labRect.x + 5, labRect.y + 5);
            int ly = labRect.y + 30;
            for (const auto& it : labItems) {
                renderText(renderer, font, it, labRect.x + 20, ly);
                ly += 24;
            }

            // Search button
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderFillRect(renderer, &searchBtn);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &searchBtn);
            TTF_SizeUTF8(font, "Recherche", &tw, &th);
            renderText(renderer, font, "Recherche",
                       searchBtn.x + (searchBtn.w - tw) / 2,
                       searchBtn.y + (searchBtn.h - th) / 2);

            int yy = labRect.y + labRect.h + 40;
            renderText(renderer, font, "Inventaire", invRect.x + 20, yy);
            yy += 30;
            const auto& items = hero.inventaire.getItems();
            for (size_t i = 0; i < items.size(); ++i) {
                SDL_Rect r{invRect.x + 40, yy, invRect.w - 80, 24};
                renderText(renderer, font, items[i], r.x, r.y);
                itemRects.push_back(r);
                yy += 24;
            }

            renderText(renderer, font, "Echap pour fermer", invRect.x + 20,
                       invRect.y + invRect.h - 30);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    saveCharacter(hero, "savegame.txt");
    TTF_CloseFont(font);
}
