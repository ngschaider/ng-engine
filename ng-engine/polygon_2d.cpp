#include "polygon_2d.h"
#include "vector2.h"
#include <vector>

Polygon2D::Polygon2D(std::vector<Vector2> vertices) : vertices(vertices) {

}

std::vector<Vector2> Polygon2D::getEdges() {
	std::vector<Vector2> edges;

	for (int i = 0; i < this->vertices.size(); i++) {
		Vector2 thisPoint = this->vertices[i];
		Vector2 nextPoint = this->vertices[(i + 1) % this->vertices.size()];

		edges.push_back(nextPoint - thisPoint);
	}

	return edges;
}

std::vector<float> Polygon2D::project(Vector2 axis) {
	std::vector<float> distances;
	for (Vector2 vertex : this->vertices) {
		distances.push_back(vertex.dot(axis));
	}
	return distances;
}

Vector2 Polygon2D::getArithmeticMean() {
	Vector2 sum = Vector2(0, 0);

	for (Vector2 vertex : this->vertices) {
		sum = sum + vertex;
	}

	return sum / (float) this->vertices.size();
}

Vector2 Polygon2D::getClosestVertex(Vector2 point) {
	float minDistance = INFINITY;
	int index = -1;

	for (int i = 0; i < this->vertices.size(); i++) {
		Vector2 vertex = this->vertices[i];
		float distance = point.distance(vertex);

		if (distance < minDistance) {
			minDistance = distance;
			index = i;
		}
	}

	return this->vertices[index];
}