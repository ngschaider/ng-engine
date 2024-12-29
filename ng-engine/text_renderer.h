#pragma once

#include "font.h"
#include "renderer.h"
#include <string>
#include <map>

/**
* Renders text.
*/
class TextRenderer : public Renderer {
private:
	/**
	* Vertex array object
	*/
	unsigned int VAO;

	/**
	* Vertex buffer object
	*/
	unsigned int VBO;
public:
	/**
	* The color the text should be renderd in.
	*/
	Color color = Color::white();

	/**
	* The font to use for rendering
	*/
	Font* font;
	 
	/**
	* The text to render
	*/
	std::string text;

	/**
	* Constructs a new TextRenderer instance and sets up the required graphics memory.
	* The text is assumed to get set later.
	*/
	TextRenderer();

	/**
	* Constructs a new TextRenderer instance and sets up the required graphics memory using the given text.
	*/
	TextRenderer(std::string text);

	/**
	* The render signal of the render system. Renders the text.
	*/
	void render() override;
};