#pragma once

#include "renderer.h"
#include <string>

class TextRenderer : public Renderer {
public:
	TextRenderer();
	TextRenderer(std::string);
	std::string text;
	void render() override;
};