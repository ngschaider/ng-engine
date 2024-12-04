#include "triangle_renderer.h"
#include "graphics.h"

TriangleRenderer::TriangleRenderer() {

}

void TriangleRenderer::render(Graphics* graphics) {
	Renderer::render(graphics);

	graphics->triangle();
}