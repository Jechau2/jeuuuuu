#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <string>

int showMenu(SDL_Window* window, SDL_Renderer* renderer,
             int &width, int &height, int &targetFPS, std::string &language);

#endif // MENU_H
