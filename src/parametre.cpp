#include "parametre.h"
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>

static void renderOption(SDL_Renderer* renderer, TTF_Font* font,
                         const std::string& text, int x, int y, bool selected) {
    SDL_Color color = selected ? SDL_Color{255, 255, 0, 255}
                               : SDL_Color{255, 255, 255, 255};
    SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!surf) {
        std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dst{x, y, surf->w, surf->h};
    SDL_FreeSurface(surf);
    if (tex) {
        SDL_RenderCopy(renderer, tex, nullptr, &dst);
        SDL_DestroyTexture(tex);
    }
}

static void renderSliderOption(SDL_Renderer* renderer, TTF_Font* font,
                               const std::string& label,
                               const std::vector<std::string>& options,
                               int index, int x, int y, bool selected) {
    std::string line = label + ": ";
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == static_cast<size_t>(index))
            line += "[" + options[i] + "]";
        else
            line += options[i];
        if (i + 1 < options.size()) line += " | ";
    }
    renderOption(renderer, font, line, x, y, selected);
}

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

