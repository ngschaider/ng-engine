#pragma once

#include "renderer.h"

class SquareRenderer : public Renderer {
private:
	unsigned int VAO_fill;
	unsigned int VAO_stroke;
public:
	bool doFill = true;
	bool doStroke = false;
	Color strokeColor = Color::black();
	Color fillColor = Color::white();
	SquareRenderer();
	~SquareRenderer();
	void render();
};