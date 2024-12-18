#pragma once

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
protected:
	Matrix4x4 getTransformationMatrix();
public:
	RendererSpace space = RendererSpace::Local;
	Shader* shader = nullptr;

	// int renderingOrder = 0; // Renderer instances with higher order are rendered later

	virtual void beforeRender();
	virtual void render();
	virtual void afterRender();
};