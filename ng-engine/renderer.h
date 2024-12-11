#pragma once

#include "graphics.h"
#include "component.h"
#include "color.h"
#include "shader.h"

enum class RendererSpace {
	Local,
	World,
	Camera,
	Clip,
	Screen
};

class Renderer : public Component {
private:
public:
	Color fillColor = Color::white();
	bool doFill = true;

	Color strokeColor = Color::white();
	bool doStroke = false;

	float lineWidth = 0.03f;
	float fontSize = 0.03f;

	RendererSpace space = RendererSpace::Local;

	virtual void render(Graphics*);
};