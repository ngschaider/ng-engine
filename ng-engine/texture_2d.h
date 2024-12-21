#pragma once

#include <glad/glad.h>
#include "vector2i.h"

class Texture2D {
private:
	unsigned int id;
	unsigned int width;
	unsigned int height;
	unsigned int internalFormat;
	unsigned int imageFormat;
	unsigned int wrapS;
	unsigned int wrapT;
	unsigned int filterMin;
	unsigned int filterMax;
public:
	Texture2D();
	void generate(Vector2i, unsigned char*);
	void bind() const;
	void unbind() const;
};