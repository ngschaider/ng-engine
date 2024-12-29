#include "rectangle_collider.h"
#include "polygon_2d.h"

Polygon2D RectangleCollider::getLocalPolygon() {
	return Polygon2D({
		this->rect.bottomLeft(),
		this->rect.bottomRight(),
		this->rect.topRight(),
		this->rect.topLeft(),
		});
}