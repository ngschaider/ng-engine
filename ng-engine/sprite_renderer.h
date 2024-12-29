#pragma once

#include "renderer.h"
#include "texture_2d.h"

/**
* Renders a single quad with a texture.
* ATTENTION: This is largely untested!
*/
class SpriteRenderer : public Renderer {
private:
	/**
	* The vertex array object
	*/
	unsigned int VAO;
public:
	/**
	* The 2D texture to render.
	*/
	Texture2D* texture;

	/**
	* Constructs a new SpriteRenderer and sets up the required graphics memory
	*/
	SpriteRenderer();

	/**
	* De-allocates the allocated graphics memory and destructs the object
	*/
	virtual ~SpriteRenderer();

	/**
	* The render signal of the render system. Renders the sprite.
	*/
	void render() override;
};