#include "ui_helpers.h"
#include <iostream>

/**
 * @brief Indique si un point appartient à un rectangle.
 */
bool pointInRect(int x, int y, const SDL_Rect& r) {
    return x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h;
}

/**
 * @brief Rend une option de menu texte.
 */
void renderOption(SDL_Renderer* renderer, TTF_Font* font,
                  const std::string& text, int x, int y, bool selected,
                  SDL_Rect* outRect) {
    SDL_Color color = selected ? SDL_Color{255, 255, 0, 255}
                               : SDL_Color{255, 255, 255, 255};
    SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!surf) {
        std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dst{x, y, surf->w, surf->h};
    if (outRect) *outRect = dst;
    SDL_FreeSurface(surf);
    if (tex) {
        SDL_RenderCopy(renderer, tex, nullptr, &dst);
        SDL_DestroyTexture(tex);
    }
}

/**
 * @brief Rend une option de type slider contenant plusieurs valeurs.
 */
void renderSliderOption(SDL_Renderer* renderer, TTF_Font* font,
                        const std::string& label,
                        const std::vector<std::string>& options,
                        int index, int x, int y, bool selected,
                        SDL_Rect* outRect) {
    std::string line = label + ": ";
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == static_cast<size_t>(index))
            line += "[" + options[i] + "]";
        else
            line += options[i];
        if (i + 1 < options.size()) line += " | ";
    }
    renderOption(renderer, font, line, x, y, selected, outRect);
}
