#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

struct Button {
    SDL_Rect rect;
    std::string label;
    SDL_Texture* texture{nullptr};
};

bool pointInRect(int x, int y, const SDL_Rect& r) {
    return x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    const int width = 800;
    const int height = 600;

    SDL_Window* window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    std::vector<Button> buttons;
    int btnW = 200;
    int btnH = 50;
    int centerX = (width - btnW) / 2;
    int startY = 150;
    int spacing = 20;

    buttons.push_back({{centerX, startY, btnW, btnH}, "Jouer"});
    buttons.push_back({{centerX, startY + (btnH + spacing), btnW, btnH}, "Charg\xC3\xA9"});
    buttons.push_back({{centerX, startY + 2 * (btnH + spacing), btnW, btnH}, "Param\xC3\xA8tre"});
    // quit button bottom right
    buttons.push_back({{width - btnW - 20, height - btnH - 20, btnW, btnH}, "Quitter"});

    SDL_Color textColor{255, 255, 255, 255};
    for (auto& b : buttons) {
        SDL_Surface* surf = TTF_RenderUTF8_Blended(font, b.label.c_str(), textColor);
        if (!surf) {
            std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
            continue;
        }
        b.texture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mx = e.button.x;
                int my = e.button.y;
                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (pointInRect(mx, my, buttons[i].rect)) {
                        if (i == 0) {
                            std::cout << "Jouer clicked" << std::endl;
                        } else if (i == 1) {
                            std::cout << "Charger clicked" << std::endl;
                        } else if (i == 2) {
                            std::cout << "Parametre clicked" << std::endl;
                        } else if (i == 3) {
                            running = false; // Quitter button
                        }
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

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
    }

    for (auto& b : buttons) {
        if (b.texture) SDL_DestroyTexture(b.texture);
    }
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
