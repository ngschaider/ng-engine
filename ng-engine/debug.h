#pragma once

#include "vector3.h"
#include "renderer.h"
#include "color.h"

typedef struct {
	Vector3 start;
	Vector3 end;
	Color color;
} Line;

class Debug : public Renderer {
private:
	std::vector<Line> lines;
public:
	void line(Vector3 start, Vector3 end, Color color);
	//static void circle(Vector3 center, float radius);
	//static void rect(Vector3 position, float width, float height);
	void earlyUpdate();
	void render();
};
