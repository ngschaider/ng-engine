#pragma once

#include "renderer.h"
#include "texture2d.h"

class SpriteRenderer : public Renderer {
private:
	unsigned int VAO;
public:
	SpriteRenderer();
	virtual ~SpriteRenderer();
	void render();
	Texture2D* texture;
};