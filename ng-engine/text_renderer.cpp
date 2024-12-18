#include "text_renderer.h"

TextRenderer::TextRenderer() {
	
}
TextRenderer::TextRenderer(std::string text) {
	this->text = text;
}

void TextRenderer::render() {
	Renderer::render();
}