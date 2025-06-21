#include "parametre.h"
#include "ui_helpers.h"
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>

/**
 * @brief Affiche et gère le menu des paramètres.
 *
 * Ce menu permet à l'utilisateur de choisir la langue, la résolution de la
 * fenêtre et la cadence d'images par seconde.
 * Les valeurs sélectionnées sont renvoyées via les références.
 *
 * @param window   Fenêtre SDL.
 * @param renderer Contexte de rendu.
 * @param width    Largeur de fenêtre à mettre à jour.
 * @param height   Hauteur de fenêtre à mettre à jour.
 * @param fps      FPS choisi par l'utilisateur.
 * @param language Langue sélectionnée.
 */
void showSettings(SDL_Window* window, SDL_Renderer* renderer,
                  int &width, int &height, int &fps, std::string &language) {
    std::vector<std::string> languages = {"Francais", "English"};
    int langIndex = 0;
    for (size_t i = 0; i < languages.size(); ++i)
        if (languages[i] == language) langIndex = static_cast<int>(i);

    std::vector<SDL_Point> sizes = {{800,450},{1280,720},{1920,1080}};
    std::vector<std::string> sizeLabels;
    for (const auto& s : sizes)
        sizeLabels.push_back(std::to_string(s.x) + "x" + std::to_string(s.y));
    int sizeIndex = 0;
    for (size_t i = 0; i < sizes.size(); ++i)
        if (sizes[i].x == width && sizes[i].y == height)
            sizeIndex = static_cast<int>(i);

    std::vector<int> fpsOptions = {30, 60, 120};
    std::vector<std::string> fpsLabels;
    for (int f : fpsOptions) fpsLabels.push_back(std::to_string(f));
    int fpsIndex = 1; // default 60
    for (size_t i = 0; i < fpsOptions.size(); ++i)
        if (fpsOptions[i] == fps) fpsIndex = static_cast<int>(i);

    enum Option { LANG, SIZE, FPS, COUNT };
    int current = 0;
    bool langMenu = false;

    std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    bool running = true;
    SDL_Event e;
    while (running) {
        SDL_Rect langRect{}, sizeRect{}, fpsRect{};
        std::vector<SDL_Rect> languageRects(languages.size());

        if (!langMenu) {
            std::string tmp = "Langue: " + languages[langIndex] + " v";
            int tw, th;
            TTF_SizeUTF8(font, tmp.c_str(), &tw, &th);
            langRect = {50, 80, tw, th};

            tmp = "Taille fenetre"; // We'll compute slider text with options
            std::string line = "Taille fenetre: ";
            for (size_t i=0;i<sizeLabels.size();++i){
                if(i==static_cast<size_t>(sizeIndex)) line+="["+sizeLabels[i]+"]"; else line+=sizeLabels[i];
                if(i+1<sizeLabels.size()) line+=" | ";
            }
            TTF_SizeUTF8(font, line.c_str(), &tw, &th);
            sizeRect = {50, 140, tw, th};

            line = "FPS: ";
            for(size_t i=0;i<fpsLabels.size();++i){
                if(i==static_cast<size_t>(fpsIndex)) line+="["+fpsLabels[i]+"]"; else line+=fpsLabels[i];
                if(i+1<fpsLabels.size()) line+=" | ";
            }
            TTF_SizeUTF8(font, line.c_str(), &tw, &th);
            fpsRect = {50, 200, tw, th};
        } else {
            std::string tmp = "Langue v";
            int tw, th;
            TTF_SizeUTF8(font, tmp.c_str(), &tw, &th);
            langRect = {50, 80, tw, th};

            for (size_t i=0;i<languages.size();++i){
                TTF_SizeUTF8(font, languages[i].c_str(), &tw, &th);
                languageRects[i] = {70, 120 + static_cast<int>(i)*40, tw, th};
            }

            std::string line = "Taille fenetre: ";
            for (size_t i=0;i<sizeLabels.size();++i){
                if(i==static_cast<size_t>(sizeIndex)) line+="["+sizeLabels[i]+"]"; else line+=sizeLabels[i];
                if(i+1<sizeLabels.size()) line+=" | ";
            }
            TTF_SizeUTF8(font, line.c_str(), &tw, &th);
            sizeRect = {50, 120 + static_cast<int>(languages.size()) * 40 + 40, tw, th};

            line = "FPS: ";
            for(size_t i=0;i<fpsLabels.size();++i){
                if(i==static_cast<size_t>(fpsIndex)) line+="["+fpsLabels[i]+"]"; else line+=fpsLabels[i];
                if(i+1<fpsLabels.size()) line+=" | ";
            }
            TTF_SizeUTF8(font, line.c_str(), &tw, &th);
            fpsRect = {50, sizeRect.y + 60, tw, th};
        }
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        if (langMenu)
                            langMenu = false;
                        else
                            running = false;
                        break;
                    case SDLK_RETURN:
                        if (current == LANG)
                            langMenu = !langMenu;
                        break;
                    case SDLK_UP:
                        if (langMenu)
                            langIndex = (langIndex + languages.size() - 1) % languages.size();
                        else
                            current = (current + COUNT - 1) % COUNT;
                        break;
                    case SDLK_DOWN:
                        if (langMenu)
                            langIndex = (langIndex + 1) % languages.size();
                        else
                            current = (current + 1) % COUNT;
                        break;
                    case SDLK_LEFT:
                        if (!langMenu) {
                            if (current == LANG)
                                langIndex = (langIndex + languages.size() - 1) % languages.size();
                            else if (current == SIZE)
                                sizeIndex = (sizeIndex + sizes.size() - 1) % sizes.size();
                            else if (current == FPS)
                                fpsIndex = (fpsIndex + fpsOptions.size() - 1) % fpsOptions.size();
                        }
                        break;
                    case SDLK_RIGHT:
                        if (!langMenu) {
                            if (current == LANG)
                                langIndex = (langIndex + 1) % languages.size();
                            else if (current == SIZE)
                                sizeIndex = (sizeIndex + 1) % sizes.size();
                            else if (current == FPS)
                                fpsIndex = (fpsIndex + 1) % fpsOptions.size();
                        }
                        break;
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int mx = e.button.x;
                int my = e.button.y;
                if (!langMenu) {
                    if (pointInRect(mx, my, langRect)) {
                        langMenu = !langMenu;
                        current = LANG;
                    } else if (pointInRect(mx, my, sizeRect)) {
                        sizeIndex = (sizeIndex + 1) % sizes.size();
                        current = SIZE;
                    } else if (pointInRect(mx, my, fpsRect)) {
                        fpsIndex = (fpsIndex + 1) % fpsOptions.size();
                        current = FPS;
                    }
                } else {
                    if (pointInRect(mx, my, langRect)) {
                        langMenu = false;
                    }
                    for (size_t i = 0; i < languages.size(); ++i) {
                        if (pointInRect(mx, my, languageRects[i])) {
                            langIndex = static_cast<int>(i);
                        }
                    }
                    if (pointInRect(mx, my, sizeRect)) {
                        sizeIndex = (sizeIndex + 1) % sizes.size();
                    } else if (pointInRect(mx, my, fpsRect)) {
                        fpsIndex = (fpsIndex + 1) % fpsOptions.size();
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        if (!langMenu) {
            renderOption(renderer, font,
                         "Langue: " + languages[langIndex] + " v", 50, 80,
                         current == LANG);
            renderSliderOption(renderer, font, "Taille fenetre", sizeLabels,
                               sizeIndex, 50, 140, current == SIZE);
            renderSliderOption(renderer, font, "FPS", fpsLabels,
                               fpsIndex, 50, 200, current == FPS);
            renderOption(renderer, font, "Esc pour retourner", 50, 260, false);
        } else {
            renderOption(renderer, font, "Langue v", 50, 80, current == LANG);
            for (size_t i = 0; i < languages.size(); ++i)
                renderOption(renderer, font, "  " + languages[i], 70, 120 + static_cast<int>(i)*40,
                             i == static_cast<size_t>(langIndex));
            int base = 120 + static_cast<int>(languages.size()) * 40 + 40;
            renderSliderOption(renderer, font, "Taille fenetre", sizeLabels,
                               sizeIndex, 50, base, current == SIZE);
            base += 60;
            renderSliderOption(renderer, font, "FPS", fpsLabels,
                               fpsIndex, 50, base, current == FPS);
            base += 60;
            renderOption(renderer, font, "Esc pour retourner", 50, base, false);
        }

        SDL_RenderPresent(renderer);
    }

    language = languages[langIndex];
    width = sizes[sizeIndex].x;
    height = sizes[sizeIndex].y;
    fps = fpsOptions[fpsIndex];

    SDL_SetWindowSize(window, width, height);

    TTF_CloseFont(font);
}

