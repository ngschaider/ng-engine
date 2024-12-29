#pragma once

#include "renderer.h"
#include "color.h"

/**
* Renders a triangle.
*/
class TriangleRenderer : public Renderer {
private:
	/**
	* Vertex array object
	*/
	unsigned int VAO;
public:
	/**
	* Wether the triangle should be filled
	*/
	bool doFill = true;

	/**
	* The color to use for filling the triangle
	*/
	Color fillColor = Color::white();

	/**
	* Constructs a new triangle and sets up the needed graphics memory
	*/
	TriangleRenderer();

	/**
	* The render system of the render system. Renders the triangle.
	*/
	void render() override;
};