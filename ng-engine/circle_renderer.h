#pragma once

#include "renderer.h"
#include "color.h"

class CircleRenderer : public Renderer {
private:
	unsigned int VAO;
public:
	bool doFill = true;
	Color fillColor = Color::white();

	CircleRenderer();
	void render() override;
};