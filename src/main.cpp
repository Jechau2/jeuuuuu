#include "GameAI.h"
#include "menu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <filesystem>
#include <iostream>
#include <string>

/**
 * @brief Point d'entrée de l'application.
 *
 * Initialise SDL et SDL_ttf, crée la fenêtre principale puis lance le menu.
 * Les ressources sont libérées avant la sortie du programme.
 */
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

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    int width = 800;
    int height = 600;
    int targetFPS = 60;
    std::string language = "Francais";

    SDL_Window* window = SDL_CreateWindow("l'arme fatale", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
    std::filesystem::path iconPath = (exePath.parent_path() / ".." / "assets" / "icon.png").lexically_normal();
    if (SDL_Surface* icon = IMG_Load(iconPath.string().c_str())) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    } else {
        std::cerr << "Failed to load icon: " << iconPath << " - " << IMG_GetError() << std::endl;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Demonstration of the AI integration
    std::filesystem::path scriptPath = (exePath.parent_path() / ".." / "scripts" /
                                        "ai_prompt.py")
                                           .lexically_normal();
    GameAI ai(scriptPath.string());
    std::string response = ai.generateObject("Cr\xC3\xA9e un objet magique pour un jeu en C++");
    std::cout << "GameAI: " << response << std::endl;

    int result = showMenu(window, renderer, width, height, targetFPS, language);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return result;
}
