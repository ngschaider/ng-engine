#pragma once

#include "font.h"
#include "renderer.h"
#include <string>
#include <map>

class TextRenderer : public Renderer {
private:
	unsigned int VAO;
	unsigned int VBO;
public:
	Font* font;
	std::string text;
	TextRenderer();
	TextRenderer(std::string text);
	void render() override;
	Color color = Color::white();
};