#pragma once

#include "polygon_collider_2d.h"
#include "polygon_2d.h"
#include "rect.h"

/**
* A collider featuring a rectangular shape
*/
class RectangleCollider : public PolygonCollider2D {
public:
	/**
	* The rectangle specifying the collider's shape.
	*/
	Rect rect = Rect(Vector2(0, 0), Vector2(1, 1), AnchorPoint::CenterCenter);

	/**
	* Returns the polygon of the collider in local space.
	*/
	Polygon2D getLocalPolygon();
};