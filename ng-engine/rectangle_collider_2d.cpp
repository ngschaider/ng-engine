#include "rectangle_collider_2d.h"
#include "polygon_2d.h"

Polygon2D RectangleCollider2D::getLocalPolygon() {
	return Polygon2D({
		this->rect.bottomLeft(),
		this->rect.bottomRight(),
		this->rect.topRight(),
		this->rect.topLeft(),
		});
}

RectangleCollider2D::RectangleCollider2D() {

}