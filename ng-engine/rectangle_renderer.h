#pragma once

#include "renderer.h"

class RectangleRenderer : public Renderer {
private:
	unsigned int VAO_fill;
	unsigned int VAO_stroke;
public:
	bool doFill = true;
	bool doStroke = false;
	Color strokeColor = Color::black();
	Color fillColor = Color::white();
	RectangleRenderer();
	~RectangleRenderer();
	void render();
};