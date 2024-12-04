#pragma once
#include "renderer.h"
#include "graphics.h"

class RectangleRenderer : public Renderer {
public:
	RectangleRenderer();
	void render(Graphics*);
};