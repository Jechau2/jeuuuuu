#include "character_creation.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

// Simple text rendering helper
static void renderText(SDL_Renderer* r, TTF_Font* f, const std::string& t,
                       int x, int y, SDL_Color c = {0xE0,0xE0,0xE0,0xFF},
                       bool center = false) {
    SDL_Surface* s = TTF_RenderUTF8_Blended(f, t.c_str(), c);
    if (!s) return;
    SDL_Texture* tx = SDL_CreateTextureFromSurface(r, s);
    SDL_Rect dst{x, y, s->w, s->h};
    if (center) dst.x -= s->w/2;
    SDL_FreeSurface(s);
    if (tx) { SDL_RenderCopy(r, tx, nullptr, &dst); SDL_DestroyTexture(tx); }
}

// Handle a 4x4 sprite sheet of 16x16 sprites
class SpriteSheet {
  public:
    explicit SpriteSheet(SDL_Texture* t) : tex(t) {}
    void render(SDL_Renderer* r, int idx, int x, int y, int scale) {
        if (!tex) return;
        SDL_Rect src{(idx%4)*16, (idx/4)*16, 16, 16};
        SDL_Rect dst{x, y, 16*scale, 16*scale};
        SDL_RenderCopy(r, tex, &src, &dst);
    }
  private:
    SDL_Texture* tex{};
};

// Allow selection and modification of a stat
class StatSelector {
  public:
    StatSelector(const std::string& n, int* v) : name(n), val(v), base(*v) {}
    void change(int d, int& remain) {
        if (d>0 && remain>0) { (*val)++; remain--; }
        else if (d<0 && *val>base) { (*val)--; remain++; }
    }
    void render(SDL_Renderer* r, TTF_Font* f, int x, int y, bool sel) {
        SDL_Color c = sel ? SDL_Color{0x46,0xC4,0xF3,0xFF}
                          : SDL_Color{0xE0,0xE0,0xE0,0xFF};
        renderText(r, f, name + ": " + std::to_string(*val), x, y, c);
    }
  private:
    std::string name;
    int* val;
    int base;
};

bool showCharacterCreation(SDL_Window* window, SDL_Renderer* renderer, Character& hero) {
    int width, height; SDL_GetWindowSize(window, &width, &height);
    const int targetFPS = 60;
    std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 20);
    if (!font) { std::cerr << "Failed to load font: " << TTF_GetError() << std::endl; return false; }

    SDL_Surface* surf = IMG_Load("assets/character_creator/hero_sheet.png");
    SDL_Texture* sheetTex = nullptr;
    if (surf) { sheetTex = SDL_CreateTextureFromSurface(renderer, surf); SDL_FreeSurface(surf); }
    else std::cerr << "Missing hero_sheet.png: " << IMG_GetError() << std::endl;
    surf = IMG_Load("assets/character_creator/frame.png");
    SDL_Texture* frameTex = nullptr;
    if (surf) { frameTex = SDL_CreateTextureFromSurface(renderer, surf); SDL_FreeSurface(surf); }
    surf = IMG_Load("assets/character_creator/cursor.png");
    SDL_Texture* cursorTex = nullptr;
    if (surf) { cursorTex = SDL_CreateTextureFromSurface(renderer, surf); SDL_FreeSurface(surf); }

    SpriteSheet sheet(sheetTex);

    Character tmp = hero;
    tmp.force = tmp.defense = tmp.agilite = tmp.intelligence = 5;
    int remaining = 4;
    StatSelector stats[] = {
        {"Force", &tmp.force},
        {"Defense", &tmp.defense},
        {"Agilite", &tmp.agilite},
        {"Intelligence", &tmp.intelligence}
    };

    std::string name;
    int sprite = 0;
    int step = 0; // 0 sprite, 1 name, 2 stats
    int statSel = 0;
    bool running = true, confirm = false;
    SDL_StartTextInput();
    SDL_Event e;
    while (running) {
        Uint32 start = SDL_GetTicks();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = false; confirm = false; }
            else if (e.type == SDL_KEYDOWN) {
                SDL_Keycode k = e.key.keysym.sym;
                if (k == SDLK_ESCAPE) { running = false; confirm = false; }
                else if (step==0) {
                    if (k==SDLK_LEFT) sprite = (sprite+15)%16;
                    else if (k==SDLK_RIGHT) sprite = (sprite+1)%16;
                    else if (k==SDLK_UP) sprite = (sprite+12)%16;
                    else if (k==SDLK_DOWN) sprite = (sprite+4)%16;
                    else if (k==SDLK_RETURN || k==SDLK_KP_ENTER) step=1;
                } else if (step==1) {
                    if (k==SDLK_RETURN || k==SDLK_KP_ENTER) step=2;
                    else if (k==SDLK_BACKSPACE && !name.empty()) name.pop_back();
                } else if (step==2) {
                    if (k==SDLK_RETURN || k==SDLK_KP_ENTER) { confirm=true; running=false; }
                    else if (k==SDLK_UP) statSel = (statSel+3)%4;
                    else if (k==SDLK_DOWN) statSel = (statSel+1)%4;
                    else if (k==SDLK_LEFT || k==SDLK_MINUS || k==SDLK_KP_MINUS) stats[statSel].change(-1, remaining);
                    else if (k==SDLK_RIGHT || k==SDLK_PLUS || k==SDLK_KP_PLUS || k==SDLK_EQUALS) stats[statSel].change(1, remaining);
                }
            } else if (e.type == SDL_TEXTINPUT && step==1) {
                if (name.size() < 12) name += e.text.text;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x30,0x3C,0x3C,255);
        SDL_RenderClear(renderer);

        int sx = width/2 - 32;
        int sy = 40;
        if (frameTex) { SDL_Rect d{sx-4, sy-4, 72, 72}; SDL_RenderCopy(renderer, frameTex, nullptr, &d); }
        sheet.render(renderer, sprite, sx, sy, 4);

        std::string disp = "Nom: " + name; if(step==1 && (SDL_GetTicks()/300)%2==0 && name.size()<12) disp += "_";
        renderText(renderer, font, disp, width/2, 120, {0xE0,0xE0,0xE0,0xFF}, true);

        int y = 170;
        for (int i=0;i<4;++i) {
            stats[i].render(renderer, font, width/2 - 40, y, step==2 && statSel==i);
            if (step==2 && statSel==i && cursorTex) {
                SDL_Rect d{width/2 - 60, y, 16,16};
                SDL_RenderCopy(renderer, cursorTex, nullptr, &d);
            }
            y += 30;
        }
        renderText(renderer, font, "Points: " + std::to_string(remaining), width/2, y+10, {0xE0,0xE0,0xE0,0xFF}, true);

        SDL_RenderPresent(renderer);
        Uint32 frameTime = SDL_GetTicks() - start;
        Uint32 delay = 1000/targetFPS;
        if (frameTime < delay) SDL_Delay(delay - frameTime);
    }
    SDL_StopTextInput();
    if (sheetTex) SDL_DestroyTexture(sheetTex);
    if (frameTex) SDL_DestroyTexture(frameTex);
    if (cursorTex) SDL_DestroyTexture(cursorTex);
    TTF_CloseFont(font);

    if (confirm) {
        hero = tmp;
        hero.nom = name.empty() ? hero.nom : name;
        hero.sprite = sprite;
    }
    return confirm;
}

