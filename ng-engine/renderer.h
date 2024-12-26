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

	/**
	* Called before the render cycle.
	*/
	virtual void beforeRender();

	/**
	* Called during the render cycle.
	*/
	virtual void render();

	/**
	* Called after the render cycle.
	*/
	virtual void afterRender();
};