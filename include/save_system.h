#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#include "character.h"
#include <string>

bool saveCharacter(const Character& hero, const std::string& filename);
bool loadCharacter(Character& hero, const std::string& filename);

#endif // SAVE_SYSTEM_H
