#pragma once

#include "vector3.h"
#include "renderer.h"
#include "color.h"
#include "rect.h"

typedef struct {
	Vector3 start;
	Vector3 end;
} Line;

typedef struct {
	Vector3 position;
	float radius;
} Circle;

class Debug : public Renderer {
private:
	std::vector<Line> lines;
	std::vector<Rect> rectangles;
	std::vector<Circle> circles;
public:
	void line(Vector3 start, Vector3 end);
	void rect(Rect rect);
	void circle(Vector3 center, float radius);

	void earlyUpdate();
	void render();
};
