#pragma once

#include "renderer.h"

/**
* Renders a line. The line start and end is adjustible.
*/
class LineRenderer : public Renderer {
private:
	/**
	* The vertex array object.
	*/
	unsigned int VAO;
public:
	/**
	* The starting point of the line
	*/
	Vector3 start = Vector3(0, 0, 0);

	/**
	* The end point of the line
	*/
	Vector3 end = Vector3(1, 0, 0);

	/**
	* Constructs a new LineRenderer instance.
	*/
	LineRenderer();

	/**
	* De-allocates the allocated graphics memory and destructs the object.
	*/
	virtual ~LineRenderer();

	/**
	* The render signal of the render system. Renders the line.
	*/
	void render() override;
};