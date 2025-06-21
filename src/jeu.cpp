#include "jeu.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>

static void renderText(SDL_Renderer* renderer, TTF_Font* font,
                       const std::string& text, int x, int y) {
    SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(),
                                               SDL_Color{255,255,255,255});
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

void showCharacterPage(SDL_Window* window, SDL_Renderer* renderer, const Personage& perso) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    int infoHeight = height / 3; // bottom third for info box
    SDL_Rect infoRect{0, height - infoHeight, width, infoHeight};

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

        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
        SDL_RenderFillRect(renderer, &infoRect);

        int y = infoRect.y + 10;
        renderText(renderer, font, "Nom: " + perso.nom, 20, y);        y += 25;
        renderText(renderer, font, "Niveau: " + std::to_string(perso.niveau), 20, y);        y += 25;
        renderText(renderer, font, "PV: " + std::to_string(perso.pointsDeVie), 20, y);        y += 25;
        renderText(renderer, font, "PM: " + std::to_string(perso.pointsDeMagie), 20, y);        y += 25;
        renderText(renderer, font, "Force: " + std::to_string(perso.force), 20, y);        y += 25;
        renderText(renderer, font, "Defense: " + std::to_string(perso.defense), 20, y);        y += 25;

        renderText(renderer, font, "ESC pour quitter", width - 180, infoRect.y + infoHeight - 30);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
}
