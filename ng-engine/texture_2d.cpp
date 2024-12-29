#include "texture_2d.h"
#include "vector2i.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Texture2D::Texture2D() {
	glGenTextures(1, &this->id);
}

void Texture2D::generate(Vector2i size, unsigned char* data) {
	this->width = size.x();
	this->height = size.y();

	// Load Texture Data
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, this->width, this->height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);

	// set texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
	
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const {
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture2D::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}