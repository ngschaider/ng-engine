#pragma once

#include "renderer.h"
#include "color.h"

class TriangleRenderer : public Renderer {
private:
	unsigned int VAO_fill;
	unsigned int VAO_stroke;
public:
	bool doFill = true;
	bool doStroke = false;
	Color fillColor = Color::white();
	Color strokeColor = Color::black();

	TriangleRenderer();
	void render() override;
};