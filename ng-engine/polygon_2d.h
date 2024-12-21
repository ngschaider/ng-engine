#pragma once

#include "vector2.h"
#include <vector>

class Polygon2D {
private:
public:
	std::vector<Vector2> vertices;
	Polygon2D(std::vector<Vector2> vertices);
	std::vector<Vector2> getEdges();
	std::vector<float> project(Vector2 axis);
	Vector2 getArithmeticMean();
	Vector2 getClosestVertex(Vector2 point);
};