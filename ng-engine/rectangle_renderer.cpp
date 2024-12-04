#include "rectangle_renderer.h"
#include "graphics.h"

RectangleRenderer::RectangleRenderer() {

}

void RectangleRenderer::render(Graphics* graphics) {
	Renderer::render(graphics);

	graphics->rectangle();
}