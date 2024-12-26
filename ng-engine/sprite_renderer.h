#pragma once

#include "renderer.h"
#include "texture_2d.h"

class SpriteRenderer : public Renderer {
private:
	unsigned int VAO;
public:
	SpriteRenderer();
	virtual ~SpriteRenderer();
	void render() override;
	Texture2D* texture;
};