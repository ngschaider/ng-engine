#pragma once

#include "renderer.h"
#include "color.h"

/**
* Renders a circle using a single quad and a specialized fragment shader.
* The circle's radius is always 1 and it's center is located at (0, 0).
*/
class CircleRenderer : public Renderer {
private:
	/**
	* The vertex array object holding the information about the renderer
	*/
	unsigned int VAO;
public:
	/**
	* Wether the circle should be filled
	*/
	bool doFill = true;

	/**
	* The color to use for filling the circle.
	*/
	Color fillColor = Color::white();

	/**
	* Constructs a new CircleRenderer.
	*/
	CircleRenderer();

	/**
	* De-allocates allocated graphics memory and destrucs the object.
	*/
	virtual ~CircleRenderer();

	/**
	* The render signal of the rendering system. Renders the circle.
	*/
	void render() override;
};