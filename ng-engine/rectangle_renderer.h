#pragma once

#include "renderer.h"

/**
* Renders a rectangle.
*/
class RectangleRenderer : public Renderer {
private:
	unsigned int VAO;
public:
	/**
	* Wether the rectangle should be filled
	*/
	bool doFill = true;

	/**
	* The color to use for filling the rectangle
	*/
	Color fillColor = Color::white();

	/**
	* Constructs a new RectangleRenderer instance.
	*/
	RectangleRenderer();

	/**
	* De-allocates the allocated graphics memory and destructs the object.
	*/
	virtual ~RectangleRenderer();

	/**
	* The render signal of the render system. Renders the rectangle.
	*/
	void render() override;
};