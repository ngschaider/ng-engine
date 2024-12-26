#pragma once

#include "vector2.h"
#include <vector>

/**
* Represents a 2D polygon.
* All vertices are assumed to be in counter clockwise order.
* All positions are local to the polygon. No transformations are applied.
*/
class Polygon2D {
private:
public:
	/**
	* Position of all vertices
	*/
	std::vector<Vector2> vertices;

	/**
	* Constructs a new 2D polygon with the given vertices
	*/
	Polygon2D(std::vector<Vector2> vertices);

	/**
	* Returns the edges of the polygon. The edges are represented by vectors pointing from one vertex to the next.
	* The edges are sorted in counter clockwise order.
	*/
	std::vector<Vector2> getEdges();

	/**
	* Returns a vector containing the projection of the vertices on the given axis.
	*/
	std::vector<float> project(Vector2 axis);

	/**
	* Returns the arithmetic mean of all vertices' position.
	*/
	Vector2 getArithmeticMean();

	/**
	* Returns the closest vertex to the given point.
	*/
	Vector2 getClosestVertex(Vector2 point);
};