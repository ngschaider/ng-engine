#pragma once

#include "component.h"
#include "color.h"
#include "shader.h"

/**
* Which space are we talking about?
*/
enum class RendererSpace {
	Local,
	World,
	Camera,
	Clip,
	Screen
};

/**
* Generic base class for components that render something to the screen.
*/
class Renderer : public Component {
protected:
	/**
	* Returns the transformation matrix that should be used in the shader.
	* The returned matrix transforms the values from the RendererSpace set to clip space.
	*/
	Matrix4x4 getTransformationMatrix();
public:
	/**
	* The renderer space that the transformation matrix returned by getTransformationMatrix() transforms from.
	*/
	RendererSpace space = RendererSpace::Local;

	/**
	* The shader used for rendering. This does not have to get used but is so common amongst all renderers so that it makes sense to put it in a common place.
	*/
	Shader* shader = nullptr;

	/**
	* The before render signal of the render system. Available to be overwritten in child classes.
	*/
	virtual void beforeRender();

	/**
	* The render signal of the render system. Available to be overwritten in child classes.
	*/
	virtual void render();

	/**
	* The after render signal of the render system. Available to be overwritten in child classes.
	*/
	virtual void afterRender();
};