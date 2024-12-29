#include <exception>
#include <glad/glad.h>
#include <string>
#include <utility>
#include "font.h"
#include "freetype/freetype.h"
#include "vector2.h"

Font::Font(std::string path) {
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		throw new std::exception("Could not init FreeType Library");
	}

	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face)) {
		throw new std::exception("Failed to load font");
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			throw new std::exception("Failed to load glyph");
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Vector2 size = Vector2(face->glyph->bitmap.width * 1.0f, face->glyph->bitmap.rows * 1.0f);
		Vector2 bearing = Vector2(face->glyph->bitmap_left * 1.0f, face->glyph->bitmap_top * 1.0f);
		int advance = (int)face->glyph->advance.x;

		LoadedCharacter character = LoadedCharacter(texture, size, bearing, advance);
		this->characters.insert(std::pair<char, LoadedCharacter>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}