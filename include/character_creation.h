#ifndef CHARACTER_CREATION_H
#define CHARACTER_CREATION_H

#include <SDL2/SDL.h>
#include "character.h"

/** Show character creation menu.
 *  Returns false if user cancels.
 */
bool showCharacterCreation(SDL_Window* window, SDL_Renderer* renderer, Character& hero);

#endif // CHARACTER_CREATION_H
