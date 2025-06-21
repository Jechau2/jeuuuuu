#include "jouet.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>

void showCharacterPanel(SDL_Window* window, SDL_Renderer* renderer, const Personage& perso) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    int boxHeight = height / 3;
    SDL_Rect infoRect{0, height - boxHeight, width, boxHeight};

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &infoRect);

        int y = infoRect.y + 10;
        auto render = [&](const std::string& text) {
            SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), SDL_Color{255,255,255,255});
            if (!surf) return;
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_Rect dst{20, y, surf->w, surf->h};
            y += surf->h + 5;
            SDL_FreeSurface(surf);
            if (tex) { SDL_RenderCopy(renderer, tex, nullptr, &dst); SDL_DestroyTexture(tex); }
        };

        render("Nom: " + perso.nom);
        render("Niveau: " + std::to_string(perso.niveau));
        render("PV: " + std::to_string(perso.pointsDeVie));
        render("PM: " + std::to_string(perso.pointsDeMagie));
        render("Force: " + std::to_string(perso.force));
        render("Defense: " + std::to_string(perso.defense));

        render("ESC pour quitter");
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
}

