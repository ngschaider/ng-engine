#pragma once

#include <string>
#include <map>
#include "vector2.h"

/**
* Holds all information needed about a loaded character in the font.
*/
typedef struct {
	unsigned int textureId; // The OpenGL texture id
	Vector2 size; // The size of the character
	Vector2 bearing;
	unsigned int advance; // The advance (how much we should move in x direction)
} LoadedCharacter;

/**
* A font instance loads a font from a TTF (TrueType Font) file and stores the information.
*/
class Font {
public:
	/**
	* Holds information about the loaded characters of the font.
	*/
	std::map<char, LoadedCharacter> characters;

	/**
	* Loads a TTF file from the given file path
	*/
	Font(std::string path);
};