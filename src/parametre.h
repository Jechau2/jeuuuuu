#ifndef PARAMETRE_H
#define PARAMETRE_H

#include <SDL2/SDL.h>
#include <string>

void showSettings(SDL_Window* window, SDL_Renderer* renderer,
                  int &width, int &height, int &fps, std::string &language);

#endif // PARAMETRE_H
