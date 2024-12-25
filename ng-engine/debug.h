#pragma once

#include "vector3.h"
#include "renderer.h"
#include "color.h"

typedef struct {
	Vector3 start;
	Vector3 end;
	Color color;
	float width;
} Line;

class Debug : public Renderer {
private:
	std::vector<Line> lines;
public:
	void line(Vector3 start, Vector3 end, Color color, float width = 1);
	void earlyUpdate();
	void render();
};
