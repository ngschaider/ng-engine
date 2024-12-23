#pragma once

#include "renderer.h"

class LineRenderer : public Renderer {
private:
	unsigned int VAO;
public:
	Vector3 start = Vector3(0, 0, 0);
	Vector3 end = Vector3(1, 0, 0);
	LineRenderer();
	void render();
};