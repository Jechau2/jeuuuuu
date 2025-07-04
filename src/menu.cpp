#include "menu.h"
#include "character.h"
#include "character_creation.h"
#include "jeu.h"
#include "parametre.h"
#include "save_system.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Représente un bouton cliquable dans le menu.
 */
struct Button {
    SDL_Rect rect;
    std::string label;
    SDL_Texture* texture{nullptr};
};

/**
 * @brief Vérifie si un point se situe à l'intérieur d'un rectangle.
 *
 * @param x Coordonnée X du point.
 * @param y Coordonnée Y du point.
 * @param r Rectangle à tester.
 * @return true si le point est dans le rectangle.
 */
static bool pointInRect(int x, int y, const SDL_Rect& r) {
    return x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h;
}

/**
 * @brief Boucle d'affichage du menu principal.
 *
 * Crée les différents boutons et gère les interactions utilisateur afin de
 * lancer le jeu, charger une partie, ouvrir les paramètres ou quitter.
 *
 * @param window     Fenêtre SDL où dessiner le menu.
 * @param renderer   Contexte de rendu utilisé.
 * @param width      Largeur de fenêtre (peut être modifiée par les paramètres).
 * @param height     Hauteur de fenêtre (idem).
 * @param targetFPS  FPS cible pour la temporisation.
 * @param language   Langue actuelle de l'interface.
 * @return 0 si l'utilisateur quitte normalement.
 */
int showMenu(SDL_Window* window, SDL_Renderer* renderer,
             int& width, int& height, int& targetFPS, std::string& language) {
    std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    bool pngInit = (IMG_Init(imgFlags) & imgFlags) != 0;
    if (!pngInit) {
        std::cerr << "Failed to init SDL_image: " << IMG_GetError() << std::endl;
    }

    SDL_Texture* background = nullptr;
    const std::string pngPath = "assets/backgrounds/menu.png";
    const std::string bmpPath = "assets/backgrounds/menu.bmp";
    SDL_Surface* surf = nullptr;
    if (pngInit)
        surf = IMG_Load(pngPath.c_str());
    if (!surf)
        surf = SDL_LoadBMP(bmpPath.c_str());
    if (surf) {
        background = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        if (background) {
            std::cout << "Menu background loaded." << std::endl;
        } else {
            std::cerr << "Failed to create background texture from image" << std::endl;
        }
    } else {
        std::cerr << "Failed to load background image" << std::endl;
    }

    std::vector<Button> buttons;
    int btnW = 200;
    int btnH = 50;
    int startY = 150;
    int spacing = 20;

    /**
     * @brief Met à jour la texture des boutons en fonction de la taille de la fenêtre.
     */
    auto updateButtons = [&]() {
        int centerX = (width - btnW) / 2;
        buttons.clear();
        buttons.push_back({{centerX, startY, btnW, btnH}, "Nouveau"});
        buttons.push_back({{centerX, startY + (btnH + spacing), btnW, btnH}, "Jouer"});
        buttons.push_back({{centerX, startY + 2 * (btnH + spacing), btnW, btnH}, "Charg\xC3\xA9"});
        buttons.push_back({{centerX, startY + 3 * (btnH + spacing), btnW, btnH}, "Param\xC3\xA8tre"});
        buttons.push_back({{width - btnW - 20, height - btnH - 20, btnW, btnH}, "Quitter"});
        for (auto& b : buttons) {
            if (b.texture) {
                SDL_DestroyTexture(b.texture);
                b.texture = nullptr;
            }
            SDL_Surface* surf = TTF_RenderUTF8_Blended(font, b.label.c_str(), SDL_Color{255, 255, 255, 255});
            if (surf) {
                b.texture = SDL_CreateTextureFromSurface(renderer, surf);
                SDL_FreeSurface(surf);
            }
        }
    };

    updateButtons();

    bool running = true;
    SDL_Event e;
    while (running) {
        Uint32 frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mx = e.button.x;
                int my = e.button.y;
                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (pointInRect(mx, my, buttons[i].rect)) {
                        if (i == 0) {
                            Character hero;
                            if (showCharacterCreation(window, renderer, hero))
                                showGame(window, renderer, hero);
                            updateButtons();
                        } else if (i == 1) {
                            Character hero;
                            showGame(window, renderer, hero);
                            updateButtons();
                        } else if (i == 2) {
                            Character hero;
                            if (!loadCharacter(hero, "savegame.txt")) {
                                std::cout << "Aucune sauvegarde.\n";
                            } else {
                                showGame(window, renderer, hero);
                                updateButtons();
                            }
                        } else if (i == 3) {
                            showSettings(window, renderer, width, height, targetFPS, language);
                            updateButtons();
                        } else if (i == 4) {
                            running = false; // Quitter button
                        }
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (background) {
            SDL_Rect dst{0, 0, width, height};
            SDL_RenderCopy(renderer, background, nullptr, &dst);
        }

        for (const auto& b : buttons) {
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderFillRect(renderer, &b.rect);
            if (b.texture) {
                int tw, th;
                SDL_QueryTexture(b.texture, nullptr, nullptr, &tw, &th);
                SDL_Rect dst{b.rect.x + (b.rect.w - tw) / 2, b.rect.y + (b.rect.h - th) / 2, tw, th};
                SDL_RenderCopy(renderer, b.texture, nullptr, &dst);
            }
        }

        SDL_RenderPresent(renderer);
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        Uint32 delay = 1000 / static_cast<Uint32>(targetFPS);
        if (frameTime < delay)
            SDL_Delay(delay - frameTime);
    }

    for (auto& b : buttons) {
        if (b.texture)
            SDL_DestroyTexture(b.texture);
    }
    if (background)
        SDL_DestroyTexture(background);
    TTF_CloseFont(font);
    if (pngInit)
        IMG_Quit();
    return 0;
}
