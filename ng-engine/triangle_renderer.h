#pragma once
#include "graphics.h"
#include "renderer.h"

class TriangleRenderer : public Renderer {
public:
	TriangleRenderer();
	void render(Graphics*);
};