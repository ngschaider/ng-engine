#pragma once

#include <string>
#include <map>
#include "vector2.h"

typedef struct {
	unsigned int textureId;
	Vector2 size;
	Vector2 bearing;
	unsigned int advance;
} LoadedCharacter;

class Font {
public:
	std::map<char, LoadedCharacter> characters;
	Font(std::string path);
};