#pragma once

#include <glad/glad.h>
#include "vector2i.h"

/**
* A two-dimensional texture
*/
class Texture2D {
private:
	/**
	* The OpenGL identifier of the texture in graphics memory.
	*/
	unsigned int id;

	/**
	* The width of the texture in pixels.
	*/
	unsigned int width = 0;

	/**
	* The height of the texture in pixels.
	*/
	unsigned int height = 0;

	/**
	* The internal format of the texture 
	*/
	unsigned int internalFormat = 0;

	/**
	* The image format of the texture
	*/
	unsigned int imageFormat = 0;

	/**
	* The wrap mode for texture coordinate S
	*/
	unsigned int wrapS = 0;

	/**
	* The wrap mode for texture coordinate T
	*/
	unsigned int wrapT = 0;

	/**
	* The GL_TEXTURE_MIN_FILTER texture parameter
	*/
	unsigned int filterMin = 0;

	/**
	* The GL_TEXTURE_MAX_FILTER texture parameter
	*/
	unsigned int filterMax = 0;
public:
	/**
	* Constructs a new Texture2D instance and sets up the required graphics memory
	*/
	Texture2D();

	/**
	* Generates the texture using the given size and pixel data
	*/
	void generate(Vector2i size, unsigned char* data);

	/**
	* Binds the texture to the current OpenGL context
	*/
	void bind() const;

	/**
	* Unbinds the texture from the current OpenGL context
	*/
	void unbind() const;
};