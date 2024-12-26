#include "polygon_collider_2d.h"
#include "vector2.h"
#include "transform.h"
#include <exception>
#include "polygon_2d.h"
#include "rect.h"
#include "matrix4x4.h"
#include <vector>

Polygon2D PolygonCollider2D::getLocalPolygon() {
	throw new std::exception("PolygonCollider2D::getLocalPolygon() should be overwritten in child class.");
}

Polygon2D PolygonCollider2D::getWorldPolygon() {
	std::vector<Vector2> worldVertices;

	for (Vector2 localVertex : this->getLocalPolygon().vertices) {
		Vector2 worldVertex = this->transform()->localToWorld(localVertex);
		worldVertices.push_back(worldVertex);
	}

	return worldVertices;
}

Rect PolygonCollider2D::getLocalBounds() {
	Polygon2D p = this->getLocalPolygon();

	float minX = 0;
	float maxX = 0;
	float minY = 0;
	float maxY = 0;

	for (Vector2 vertex : p.vertices) {
		if (vertex.x() < minX) {
			minX = vertex.x();
		}
		if (vertex.x() > maxX) {
			maxX = vertex.x();
		}
		if (vertex.y() < minY) {
			minY = vertex.y();
		}
		if (vertex.y() > maxY) {
			maxY = vertex.y();
		}
	}

	Vector2 min = Vector2(minX, minY);
	Vector2 max = Vector2(maxX, maxY);

	return Rect(min, max - min, AnchorPoint::BottomLeft);
}