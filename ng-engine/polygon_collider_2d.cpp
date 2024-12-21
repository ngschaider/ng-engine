#include "polygon_collider_2d.h"
#include "polygon_2d.h"
#include "matrix4x4.h"
#include "transform.h"

Polygon2D PolygonCollider2D::getLocalPolygon() {
	throw new std::exception("PolygonCollider2D::getLocalPolygon() should be overwritten in child class.");
}

Polygon2D PolygonCollider2D::getWorldPolygon() {
	std::vector<Vector2> worldVertices;

	Matrix4x4 m = this->transform()->getLocalToWorldMatrix();
	for (Vector2 localVertex : this->getLocalPolygon().vertices) {
		Vector2 worldVertex = (m * localVertex.toVector4(0, 0)).xy();
		worldVertices.push_back(worldVertex);
	}

	return worldVertices;
}