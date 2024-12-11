#include "text_renderer.h"

TextRenderer::TextRenderer() {
	
}
TextRenderer::TextRenderer(std::string text) {
	this->text = text;
}

void TextRenderer::render(Graphics* graphics) {
	Renderer::render(graphics);

	graphics->text(this->text);
}