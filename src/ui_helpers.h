#ifndef UI_HELPERS_H
#define UI_HELPERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

bool pointInRect(int x, int y, const SDL_Rect& r);

void renderOption(SDL_Renderer* renderer, TTF_Font* font,
                  const std::string& text, int x, int y, bool selected,
                  SDL_Rect* outRect = nullptr);

void renderSliderOption(SDL_Renderer* renderer, TTF_Font* font,
                        const std::string& label,
                        const std::vector<std::string>& options,
                        int index, int x, int y, bool selected,
                        SDL_Rect* outRect = nullptr);

#endif // UI_HELPERS_H
